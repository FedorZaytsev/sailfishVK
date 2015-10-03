#include "vkhandlermessages.h"

VKHandlerMessages::VKHandlerMessages(VKStorage* storage, QObject *parent) :
    VKAbstractHandler(storage, parent)
{
    setOffset(0);
    setCount(20);
    setUserId(0);
    setStartMessageId(0);
    setReverse(0);
    m_recievedCount = 0;
    m_unreadCount = 0;
}

const QNetworkRequest VKHandlerMessages::processRequest() {
    Q_ASSERT(m_count >= 1 && m_count < 25);

    QString exec;
    if (m_offset != -1) {
        exec = QString(
"var messages = API.messages.getHistory({\"offset\":%1,\"count\":%2,\"%3_id\":%4});"
"var i = 0;"
"var users = [];"
"while (i < messages.items.length) {"
    "var message = messages.items[i];"
    "users.push(message.user_id);"
    "users.push(message.from_id);"
    "i = i + 1;"
"}"
"return {\"messages\": messages, \"users\": API.users.get({\"user_ids\":\"\"+users,\"fields\":\"photo_50,photo_100\"}), \"offset\": %1};"
).arg(m_offset).arg(m_count).arg(m_isChat?"chat":"user").arg(m_id);
    } else {
        exec = QString(
"var count = %1;"
"var off = API.messages.getHistory({\"offset\":0,\"count\":%1,\"%2_id\":%3}).unread;"
"if (parseInt(off) == 0) {"
    "off = 0;"
"}"
"if (off - %4 < 0) {"
    "off = 0;"
    "count = %1/2;"
"} else {"
    "off = off - %4;"
"}"
"var messages = API.messages.getHistory({\"offset\":off,\"count\":%1,\"%2_id\":%3});"
"var i = 0;"
"var users = [];"
"while (i < messages.items.length) {"
    "var message = messages.items[i];"
    "users.push(message.user_id);"
    "users.push(message.from_id);"
    "i = i + 1;"
"}"
"return {\"messages\": messages, \"users\": API.users.get({\"user_ids\":\"\"+users,\"fields\":\"photo_50,photo_100\"}), \"offset\": off};"
).arg(m_count*2).arg(m_isChat?"chat":"user").arg(m_id).arg(m_count);
    }


    QList<QPair<QString,QString>> args;
    args.push_back({"code",exec});
    return generateRequest("execute", args);
}

void VKHandlerMessages::processReply(QJsonValue *_reply) {
    auto reply = _reply->toObject();
    auto messages = reply.value("messages").toObject().value("items").toArray();
    auto users = reply.value("users").toArray();

    setOffset(reply.value("offset").toInt());
    m_unreadCount = reply.value("messages").toObject().value("unread").toInt();

    QVector<int> unknownUsers;
    for (auto e: messages) {
        auto message = e.toObject();

        auto msg = VKContainerMessage::fromJson(storage(), message, users, unknownUsers);
        storage()->addMessage(msg);
    }
    m_recievedCount = messages.count();

    emit partlyReady(this);

    //Additional request for case when we don't have info about users in fwd messages
    if (unknownUsers.length()) {
        qDebug()<<"We need additional users info about"<<unknownUsers;
        auto usersHandler = new VKHandlerUsers(storage(), this);
        usersHandler->setUsers(unknownUsers);
        //requestAdditionInfo(usersHandler);
    }
    //error here

    emit allDataReady(this);
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
    return m_recievedCount;
}
/*
QSharedPointer<VKContainerMessage> VKHandlerMessages::get(int i) {
    return m_messages.at(i);
}

VKContainerMessage *VKHandlerMessages::getPtr(int i) {
    return m_messages.at(i).data();
}
*/
void VKHandlerMessages::additionDataReady(VKAbstractHandler *h) {
    auto handler = dynamic_cast<VKHandlerUsers*>(h);
    Q_ASSERT(handler != nullptr);

    //qDebug()<<"additional info ready, updating";
    //for (auto e: m_messages) {
    //    e->complete(handler);
    //}

    //emit ready(this);

}
