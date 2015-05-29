#include "vkcontainermessage.h"
#include "vkcontaineruser.h"

VKContainerMessage::VKContainerMessage(QObject *parent) :
    VKAbstractContainer(parent) {
}

VKContainerMessage::~VKContainerMessage(){
}

VKContainerMessage *VKContainerMessage::fromJson(VKStorage *storage, QJsonObject obj, QJsonArray users) {
    VKContainerMessage* message = new VKContainerMessage;

    QDateTime date;
    date.setTime_t(obj.value("date").toInt());
    message->setMsgId(obj.value("id").toInt());
    message->setDate(date);
    message->setIsIncoming(obj.value("out").toInt() == 0);

    if (message->isIncoming()) {
        bool userFound = false;
        for (const auto &e : users) {
            auto el = e.toObject();
            if (el.value("id").toInt() == obj.value("user_id").toInt()) {
                auto user = VKContainerUser::fromJson(storage, el);
                message->setUser(user);
                userFound = true;
                break;
            }
        }
        Q_ASSERT(userFound);
    } else {
        message->setUser(storage->getUserById(storage->ourUserId()));
    }

    message->setReadState(obj.value("read_state").toInt() == 1);

    message->setBody(obj.value("body").toString());
    if (obj.value("chat_id").isDouble()){
        message->setChatId(obj.value("chat_id").toInt());
    } else {
        message->setChatId(obj.value("user_id").toInt());
    }


    return message;
}

VKContainerMessage *VKContainerMessage::fromSql(VKStorage* storage, QSqlQuery &query) {
    VKContainerMessage* message = new VKContainerMessage;
    message->setMsgId(query.value("id").toInt());
    QDateTime date;
    date.setTime_t(query.value("date").toInt());
    message->setDate(date);
    message->setIsIncoming(query.value("incoming").toInt());
    message->setUser(storage->getUserById(query.value("user_id").toInt()));
    message->setReadState(query.value("read_state").toInt() == 1);
    message->setBody(query.value("body").toString());
    message->setIsChat(query.value("is_chat").toInt() == 1);
    message->setChatId(query.value("chat_id").toInt());

    return message;
}

void VKContainerMessage::setUser(VKContainerUser *arg) {
    m_user = arg; m_user->setParent(this);
}

