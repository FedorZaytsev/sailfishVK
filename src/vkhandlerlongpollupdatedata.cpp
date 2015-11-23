#include "vkhandlerlongpollupdatedata.h"
#include "vkcontainerdialog.h"
#include "vkstorage.h"
#include "vkhandlerusers.h"
#include "vkcontainerdialog.h"
#include "vkcontainermessage.h"

VKHandlerLongPollUpdateData::VKHandlerLongPollUpdateData(VKStorage* storage, QObject *parent) :
    VKAbstractHandler(storage, parent)
{
}

const QNetworkRequest VKHandlerLongPollUpdateData::processRequest() {
    Q_ASSERT(m_userIds.length() || m_msgIds.length() || m_chatIds.length() || m_checkIds.length() || m_removed.length());

    Q_ASSERT(0);

    QString request;
    if (m_userIds.length()) {
        request += QString("var users = API.users.get({\"user_ids\":\"%1\", \"fields\":\"photo_50,photo_100,photo_200\"});").arg(QStringList(m_userIds).join(","));
    }

    if (m_msgIds.length()) {
        request += QString("var messages = API.messages.getById({\"message_ids\":\"%1\"});").arg(QStringList(m_msgIds).join(","));
    }

    if (m_chatIds.length()) {
        request += QString("var chats = API.messages.getById({\"message_ids\":\"%1\"});"
                           "var i = 0;"
                           "var chatUsers = [];"
                           "while (i < chats.items.length) {"
                                "var chat_active = chats.items[i].chat_active;"
                                "var ids = [chat_active[0],chat_active[1],chat_active[2],chat_active[3]];"
                                "var users = API.users.get({\"user_ids\":(ids+\",\"+chats.items[i].user_id), \"fields\":\"photo_50,photo_100\"});"
                                "chatUsers = chatUsers + users;"
                                "i = i+1;"
                           "}"
                           ).arg(QStringList(m_chatIds).join(","));
    }

    if (m_checkIds.length()) {
        request += QString("var checkChats = API.messages.getById({\"message_ids\":\"%1\"});"
                           "var a=0;"
                           "var checkMsgs=[];"
                           "var checkUsers=[];"
                           "while (a<checkChats.items.length){"
                                "var itm = checkChats.items[a];"
                                "var msgcheck;"
                                "if (!(itm.chat_id + 1 == 1)) {"
                                    "msgcheck = API.messages.getHistory({\"offset\":0,\"count\":1,\"chat_id\":itm.chat_id});"
                                "}else{"
                                    "msgcheck = API.messages.getHistory({\"offset\":0,\"count\":1,\"user_id\":itm.user_id});"
                                "}"
                                "if (itm.date > msgcheck.items[0].date){"
                                    "checkMsgs.push(msgcheck.items[0]);"
                                    "checkUsers.push(API.users.get({\"user_ids\":msgcheck.item[0].from_id, \"fields\":\"photo_50,photo_100,photo_200\"})[0]);"
                                "}"
                                "a=a+1;"
                           "}"
                           ).arg(QStringList(m_checkIds).join(","));
    }

    if (m_removed.length()) {
        request += QString("var removed = API.messages.getById({\"message_ids\":\"%1\"});"
                           "var b=0;"
                           "var removedUserIds=[];"
                           "while (b<removed.items.length){"
                                "var itm = removed.items[b];"
                                "if (itm.from_id + 1 == 1){"
                                    "removedUserIds.push(itm.user_id);"
                                "}else{"
                                    "removedUserIds.push(itm.from_id);"
                                "}"
                                "b=b+1;"
                           "}"
                           "var removedUsers = API.users.get({\"user_ids\":removedUserIds, \"fields\":\"photo_50,photo_100,photo_200\"});"
                    ).arg(QStringList(m_removed).join(","));
    }

    request += "return {";
    if (m_userIds.length()) {
        if (m_chatIds.length()) {
            request += "\"users\": (users + chatUsers)";
        } else {
            request += "\"users\": users";
        }
        if (m_msgIds.length() || m_checkIds.length() || m_removed.length()) {
            request += ",";
        }
    }
    if (m_msgIds.length()) {
        request += "\"messages\": messages";
        if (m_checkIds.length() || m_removed.length()) {
            request += ",";
        }
    }
    if (m_checkIds.length()) {
        request += "\"check\": checkMsgs, \"checkUsers\": checkUsers";
        if (m_removed.length()) {
            request += ",";
        }
    }
    if (m_removed.length()) {
        request += "\"removed\":removed.items,\"removedUsers\":removedUsers";
    }

    request += "};";


    qDebug()<<request;

    QList<QPair<QString,QString>> args;
    args.push_back({"code",request});
    return generateRequest("execute", args);
}

void VKHandlerLongPollUpdateData::processReply(QJsonValue *reply) {
    Q_UNUSED(reply);
    Q_ASSERT(0);

    /*QJsonObject data = reply->toObject();
    auto messages = data.value("messages").toObject().value("items").toArray();
    auto users = data.value("users").toArray();
    auto checkMsgs = data.value("check").toArray();
    auto checkUsers = data.value("checkUsers").toArray();
    auto removedMsgs = data.value("removed").toArray();
    auto removedUsers = data.value("removedUsers").toArray();

    for (auto e : messages) {
        auto dialog = e.toObject();
        auto dlg = VKContainerDialog::fromJson(storage(), dialog, users);
        qDebug()<<"new dialog"<<dlg->chatName()<<dlg->id()<<dlg->firstMessage()->id();
        m_updateDialogs.append(dlg);
    }

    for (auto e : checkMsgs) {
        auto message = e.toObject();
        auto msg = VKContainerMessage::fromJson(storage(), message, checkUsers);
        qDebug()<<"new message"<<msg->id()<<msg->body().mid(0,10);
        m_updateMessages.append(msg);
    }

    for (auto e : removedMsgs) {
        auto message = e.toObject();
        auto msg = VKContainerMessage::fromJson(storage(), message, removedUsers);
        qDebug()<<"new message"<<msg->id()<<msg->body().mid(0,10);
        m_updateMessages.append(msg);
    }

    for (auto e : users) {
        auto user = e.toObject();
        auto usr = VKContainerUser::fromJson(storage(), user);
        qDebug()<<"new user"<<usr->id()<<usr->firstName()<<usr->lastName();
        m_updateUsers.append(usr);
    }

    if (!unknownUsers.length()) {
        emit ready(this);
    } else {
        QStringList lst;
        for (auto e: unknownUsers) {
            lst.append(QString::number(e));
        }

        //Additional request for case when we don't have info about users in fwd messages
        qDebug()<<"We need additional users info about"<<lst.join(",");
        auto handlerUsers = new VKHandlerUsers(storage(), this);
        QVector<int> v;
        for (auto &e : lst) {
            v.push_back(e.toInt());
        }
        handlerUsers->setUsers(v);
        QObject::connect(handlerUsers, &VKHandlerUsers::allDataReady, this, &VKHandlerLongPollUpdateData::additionalInfoReady);
        vk()->sendNetworkRequest(handlerUsers);
    }*/
}

void VKHandlerLongPollUpdateData::setUserIds(QList<QString> &userIds) {
    QSet<QString> set = QSet<QString>::fromList(userIds);
    m_userIds = set.toList();
}

void VKHandlerLongPollUpdateData::setMsgIds(QList<QString> &msgIds) {
    QSet<QString> set = QSet<QString>::fromList(msgIds);
    m_msgIds = set.toList();
}

void VKHandlerLongPollUpdateData::setChatIds(QList<QString> &chatIds) {
    QSet<QString> set = QSet<QString>::fromList(chatIds);
    m_chatIds = set.toList();
}

void VKHandlerLongPollUpdateData::setCheckIds(QList<QString> &checkIds) {
    QSet<QString> set = QSet<QString>::fromList(checkIds);
    m_checkIds = set.toList();
}

void VKHandlerLongPollUpdateData::setRemoved(QList<QString> &removed) {
    QSet<QString> set = QSet<QString>::fromList(removed);
    m_removed = set.toList();
}

void VKHandlerLongPollUpdateData::setEvents(QVector<QSharedPointer<VKLPAbstract> > events) {
    m_events = events;
}

QVector<QSharedPointer<VKLPAbstract> > VKHandlerLongPollUpdateData::events() {
    return m_events;
}

QVector<QSharedPointer<VKContainerDialog> > &VKHandlerLongPollUpdateData::dialogs() {
    return m_updateDialogs;
}

QVector<QSharedPointer<VKContainerMessage> > &VKHandlerLongPollUpdateData::messages() {
    return m_updateMessages;
}

QVector<QSharedPointer<VKContainerUser> > &VKHandlerLongPollUpdateData::users() {
    return m_updateUsers;
}
/*
void VKHandlerLongPollUpdateData::additionalInfoReady(VKAbstractHandler *h) {

    VKHandlerUsers* users = dynamic_cast<VKHandlerUsers*>(h);

    for (int i=0;i<users->count();i++) {
        auto user = users->get(i);
        for (auto dialog: m_updateDialogs) {
            dialog->complete(user);
        }
        for (auto message: m_updateMessages) {
            message->complete(user);
        }
    }

}*/
