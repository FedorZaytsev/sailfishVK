#include "vkhandlermessages.h"

VKHandlerMessages::VKHandlerMessages(VKStorage* storage, QObject *parent) :
    VKAbstractHandler(storage, parent)
{
    setOffset(0);
    setCount(0);
    setUserId(0);
    setStartMessageId(0);
    setReverse(0);
}

const QNetworkRequest VKHandlerMessages::processRequest() {
    Q_ASSERT(m_count >= 20 && m_count < 25);

    QString exec = QString(
"var messages = API.messages.getHistory({\"offset\":%1,\"count\":%2,\"%3_id\":%4});"
"var i = 0;"
"var users = [];"
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

        auto msg = VKContainerMessage::fromJson(storage(), message, users, unknownUsers);
        m_messages.push_back(msg);
    }

    //Additional request for case when we don't have info about users in fwd messages
    if (unknownUsers.length()) {
        qDebug()<<"We need additional users info about"<<unknownUsers;
        auto usersHandler = new VKHandlerUsers(storage(), this);
        usersHandler->setUsers(unknownUsers);
        requestAdditionInfo(usersHandler);
    } else {
        qDebug()<<"ready";
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

QSharedPointer<VKContainerMessage> VKHandlerMessages::get(int i) {
    return m_messages.at(i);
}

VKContainerMessage *VKHandlerMessages::getPtr(int i) {
    return m_messages.at(i).data();
}

void VKHandlerMessages::additionDataReady(VKAbstractHandler *h) {
    auto handler = dynamic_cast<VKHandlerUsers*>(h);
    Q_ASSERT(handler != nullptr);

    qDebug()<<"additional info ready, updating";
    for (auto e: m_messages) {
        e->complete(handler);
    }

    emit ready(this);

}
