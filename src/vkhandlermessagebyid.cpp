#include "vkhandlermessagebyid.h"

VKHandlerMessageById::VKHandlerMessageById(VKStorage *storage, QObject *parent) :
    VKAbstractHandler(storage, parent)
{
}

const QNetworkRequest VKHandlerMessageById::processRequest() {

    QStringList sl;
    for (auto e:m_messageIds) {
        sl.append(QString::number(e));
    }

    QString exec = QString(
"var messages = API.messages.getById({\"message_ids\":\"%1\"});"
"var i = 0;"
"var users = [];"
"while (i < messages.items.length) {"
"var message = messages.items[i];"
"users.push(message.user_id);"
"users.push(message.from_id);"
"i = i + 1;"
"}"
"return {\"messages\": messages, \"users\": API.users.get({\"user_ids\":\"\"+users,\"fields\":\"photo_50,photo_100\"})};"
).arg(sl.join(","));
    QList<QPair<QString,QString>> args;
    args.push_back({"code",exec});
    return generateRequest("execute", args);
}

void VKHandlerMessageById::processReply(QJsonValue *_reply) {
    auto reply = _reply->toObject();
    auto messages = reply.value("messages").toObject().value("items").toArray();
    auto users = reply.value("users").toArray();

    for (auto e: messages) {
        auto msg = VKContainerMessage::fromJson(storage(), e.toObject(), users);
        storage()->addMessage(msg);
    }

    emit ready(this);
}

QString VKHandlerMessageById::name() {
    return "messagesById";
}

void VKHandlerMessageById::merge(VKAbstractHandler *_handler) {
    auto handler = dynamic_cast<VKHandlerMessageById*>(_handler);
    Q_ASSERT(handler);
    if (handler) {
        auto v = handler->messageIds();
        for (auto e: v) {
            add(e);
        }
    }
}

QVector<int> VKHandlerMessageById::messageIds() {
    return m_messageIds;
}

void VKHandlerMessageById::add(int id) {
    if (!m_messageIds.contains(id)) {
        m_messageIds.append(id);
    }
}
