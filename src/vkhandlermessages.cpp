#include "vkhandlermessages.h"

VKHandlerMessages::VKHandlerMessages(VKStorage* storage, QObject *parent) :
    VKAbstractHandler(storage, parent)
{
    setOffset(0);
    setCount(0);
    setUserId(0);
    setStartMessageId(0);
    setReverse(0);
    m_usersHandler = NULL;
}

const QNetworkRequest VKHandlerMessages::processRequest() {
    Q_ASSERT(m_count >= 20 && m_count < 25);

    QString exec = QString(
"var messages = API.messages.getHistory({\"offset\":%1,\"count\":%2,\"%3_id\":%4});"
"var i = 0;"
"var users = [];"
//"return messages.items.length;"
"while (i < messages.items.length) {"
    "var message = messages.items[i];"
    "users.push(message.user_id);"
    "users.push(message.from_id);"
    "i = i + 1;"
"}"
"return {\"messages\": messages, \"users\": API.users.get({\"user_ids\":\"\"+users,\"fields\":\"photo_50,photo_100\"})};"
).arg(m_offset).arg(m_count).arg(m_isChat?"chat":"user").arg(m_id);


    QList<QPair<QString,QString>> args;
    args.push_back({"code",exec});
    return generateRequest("execute", args);
}

void VKHandlerMessages::processReply(QJsonValue *reply) {
    auto messages = reply->toObject().value("messages").toObject().value("items").toArray();
    auto users = reply->toObject().value("users").toArray();

    QVector<int> unknownUsers;
    for (auto e: messages) {
        auto message = e.toObject();

        VKContainerMessage* msg = VKContainerMessage::fromJson(storage(), message, users, unknownUsers);
        msg->setParent(this);
        m_messages.push_back(msg);
    }

    QStringList lst;
    for (auto e: unknownUsers) {
        lst.append(QString::number(e));
    }

    //Additional request for case when we don't have info about users in fwd messages
    if (lst.length()) {
        qDebug()<<"We need additional users info about"<<lst.join(",");
        m_usersHandler = new VKHandlerUsers(storage(), this);
        QObject::connect(m_usersHandler, &VKHandlerUsers::ready, this, &VKHandlerMessages::usersUpdateData);
    } else {
        emit ready(this);
    }
}

QString VKHandlerMessages::name() {
    return "messages";
}

void VKHandlerMessages::setOffset(int offset) {
    m_offset = offset;
}

void VKHandlerMessages::setCount(int count) {
    m_count = count;
}

void VKHandlerMessages::setUserId(int id) {
    m_id = id;
    m_isChat = false;
}

void VKHandlerMessages::setChatId(int id) {
    m_id = id;
    m_isChat = true;
}

void VKHandlerMessages::setStartMessageId(int id) {
    m_startMsgId = id;
}

void VKHandlerMessages::setReverse(bool rev) {
    m_reverse = rev;
}

int VKHandlerMessages::count() {
    return m_messages.count();
}

VKContainerMessage *VKHandlerMessages::get(int i) {
    return m_messages.at(i);
}

void VKHandlerMessages::usersUpdateData(){
    qDebug()<<"additional info ready, updating";
    for (auto e: m_messages) {
        e->complete(m_usersHandler);
    }
    /*for (auto e: m_messages) {
        for (int i=0;i<m_usersHandler->count();i++) {
            auto el = m_usersHandler->get(i);
            if (e->user()->id() == el->id()) {
                delete e->user();
                e->setUser(el);
            }
        }
    }*/

    emit ready(this);
}
