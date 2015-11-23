#include "vkhandlerfirstmessage.h"

VKHandlerFirstMessage::VKHandlerFirstMessage(VKStorage *storage, QObject *parent) :
    VKAbstractHandler(storage, parent)
{

}

const QNetworkRequest VKHandlerFirstMessage::processRequest() {

    QStringList sl;
    for (auto e:m_chatIds) {
        sl.append(QString::number(e));
    }

    QString exec = QString(
"var chatIds=[%1];"
"var i=0;"
"var result=[];"
"var users = [];"
"while (i < chatIds.length){"
    "var message = API.messages.getHistory({\"offset\":0,\"count\":1,\"user_id\":chatIds[i]}).items[0];"
    "users.push(message.user_id);"
    "users.push(message.from_id);"
    "result.push(message);"
    "i=i+1;"
"}"
"return {\"messages\": result, \"users\": API.users.get({\"user_ids\":\"\"+users,\"fields\":\"photo_50,photo_100\"})};"
).arg(sl.join(","));

    QList<QPair<QString,QString>> args;
    args.push_back({"code",exec});
    return generateRequest("execute", args);
}

void VKHandlerFirstMessage::processReply(QJsonValue *r) {

    auto reply = r->toObject();
    auto messages = reply.value("messages").toArray();
    auto users = reply.value("users").toArray();

    for (auto e: messages) {
        if (e.isObject()) {
            auto msg = VKContainerMessage::fromJson(storage(), e.toObject(), users);
            storage()->addMessage(msg);
        }
    }
    emit ready(this);
}


QString VKHandlerFirstMessage::name() {
    return "firstMessage";
}

void VKHandlerFirstMessage::merge(VKAbstractHandler *_handler) {
    auto handler = dynamic_cast<VKHandlerFirstMessage*>(_handler);
    Q_ASSERT(handler);
    if (handler) {
        auto v = handler->chatIds();
        for (auto e: v) {
            addUserId(e);
        }
    }
}

void VKHandlerFirstMessage::addUserId(int id) {
    if (!m_chatIds.contains(id)) {
        m_chatIds.append(id);
    }
}

void VKHandlerFirstMessage::addChatId(int id) {
    if (!m_chatIds.contains(MAX_USER_ID + id)) {
        m_chatIds.append(MAX_USER_ID + id);
    }
}

QVector<int> VKHandlerFirstMessage::chatIds() {
    return m_chatIds;
}
