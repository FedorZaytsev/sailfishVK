#include "vklpmessageflagschange.h"
#include "vkcontainermessage.h"

VKLPMessageFlagsChange::VKLPMessageFlagsChange(VKStorage *storage, QObject *parent) :
    VKLPAbstract(storage, parent)
{
    m_id = 0;
    m_userId = -1;
    m_isChat = false;
    m_type = VKLPEventType::MESSAGE_FLAGS_CHANGE;
}

void VKLPMessageFlagsChange::fromLP(const QJsonArray &data) {
    qDebug()<<"fromLP";
    setId(data.at(1).toInt());
    setFlags(QSharedPointer<VKLPFlags>(new VKLPFlags(data.at(2).toInt())));
    if (data.count() > 2) {
        if (data.at(3).toInt() > MAX_USER_ID) {
            setUserId(data.at(3).toInt() - MAX_USER_ID);
        } else {
            setUserId(data.at(3).toInt());
        }
    }

    process();

}

void VKLPMessageFlagsChange::setFlags(QSharedPointer<VKLPFlags> flags) {
    m_flags = flags;

}

void VKLPMessageFlagsChange::process() {

    if (!storage()->isContainsMessage(id())) {
        deleteLater();
        return;
    }
    qDebug()<<"process";
    auto message = storage()->getMessageById(id());

    message->setIsRead(  flags()->isSet(VKLPFlags::UNREAD)   );
    message->setIsIncoming(!flags()->isSet(VKLPFlags::OUTBOX)   );
    message->setIsChat(     flags()->isSet(VKLPFlags::CHAT)     );
    message->setIsDeleted(flags()->isSet(VKLPFlags::DELETED));

    message->emitChange();
    deleteLater();
}


void VKLPMessageFlagsChange::setUserId(int id) {
    m_userId = id > MAX_USER_ID ? id - MAX_USER_ID : id;
    m_isChat = id > MAX_USER_ID;
}

bool VKLPMessageFlagsChange::needPreviousMessage() {
    return false;
}
