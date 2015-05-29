#include "vkhandlerlongpollupdatedata.h"
#include "vkcontainerdialog.h"
#include "vkstorage.h"

VKHandlerLongPollUpdateData::VKHandlerLongPollUpdateData(VKStorage* storage, QObject *parent) :
    VKAbstractHandler(storage, parent)
{
}

const QNetworkRequest VKHandlerLongPollUpdateData::processRequest() {
    QString request;
    if (m_userIds.length()) {
        request = QString("return {\"users\": API.users.get({\"user_ids\":\"%1\", \"fields\":\"photo_50,photo_100,photo_200\"});").arg(QStringList(m_userIds).join(","));
    }
    if (m_msgIds.length()) {
        request = QString("return {\"messages\": API.messages.getById({\"message_ids\":\"%1\"})};").arg(QStringList(m_userIds).join(","));
    }
    if (m_userIds.length() && m_msgIds.length()) {
        request = QString(
        "var users = API.users.get({\"user_ids\":\"%1\", \"fields\":\"photo_50,photo_100,photo_200\"});"
        "var messages = API.messages.getById({\"message_ids\":\"%2\"});"
        "return {\"users\": users, \"messages\": messages};"
        ).arg(QStringList(m_userIds).join(",")).arg(QStringList(m_msgIds).join(","));
    }

    QList<QPair<QString,QString>> args;
    args.push_back({"code",request});
    return generateRequest("execute", args);
}

bool VKHandlerLongPollUpdateData::processReply(QJsonObject *reply) {
    m_data = *reply;
/*    QJsonArray users = reply->value("users").toArray();

    for (auto e : users) {
        VKContainerUser* user = VKContainerUser::fromJson(storage(), e.toObject());
        user->setParent(this);
        storage()->addUser(user);
        m_users.append(user);
    }
    
    QJsonArray messages = reply->value("messages").toArray();

    for (auto e : messages) {
        VKContainerMessage* message = VKContainerMessage::fromJson(storage(), e.toObject(), users);
        message->setParent(this);
        storage()->addMessage(message);
        m_messages.append(message);
    }*/
    emit dataReady();
    return false;
}

void VKHandlerLongPollUpdateData::setUserIds(QList<QString> &userIds) {
    QSet<QString> set = QSet<QString>::fromList(userIds);
    m_userIds = set.toList();
}

void VKHandlerLongPollUpdateData::setMsgIds(QList<QString> &msgIds) {
    QSet<QString> set = QSet<QString>::fromList(msgIds);
    m_msgIds = set.toList();
}
