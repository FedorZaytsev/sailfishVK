#include "vklpmessageflagsset.h"
#include "vkhandlerfirstmessage.h"

VKLPMessageFlagsSet::VKLPMessageFlagsSet(VKStorage *storage, QObject *parent) :
    VKLPMessageFlagsChange(storage, parent)
{
    qDebug()<<"";
    m_type = VKLPEventType::MESSAGE_FLAGS_SET;
}


void VKLPMessageFlagsSet::completed() {
    Q_ASSERT(!m_valid);
    Q_ASSERT(storage()->isContainsMessage(id()));
    auto msg = storage()->getMessageById(id());

    if (!msg.isNull()) {
        qDebug()<<"deleting message"<<msg->id()<<msg->body().mid(0,15);
        msg->setIsDeleted(true);
        msg->emitChange();
    }
    deleteLater();
}


bool VKLPMessageFlagsSet::needPreviousMessage() {
    auto chatId = storage()->getMessageById(id())->chatId();
    if (!storage()->isContainsDialog(chatId)) {
        qDebug()<<"false";
        return false;
    }

    qDebug()<<(flags()->isSet(VKLPFlags::DELETED) && storage()->getDialogById(chatId)->firstMessage()->id() == id());
    return flags()->isSet(VKLPFlags::DELETED) && storage()->getDialogById(chatId)->firstMessage()->id() == id();
}

void VKLPMessageFlagsSet::process() {
    qDebug()<<"Setting flags for event";

    if (!storage()->isContainsMessage(id())) {
        qDebug()<<"do not contains message"<<id();

        if (storage()->isContainsDialog(userId())) {
            auto dialog = storage()->getDialogById(userId());
            dialog->setUnreadCount( dialog->unreadCount() + 1);
        }
        m_valid = true;
        deleteLater();
        return;
    }

    auto message = storage()->getMessageById(id());

    if (flags()->isSet(VKLPFlags::UNREAD)) message->setIsRead(false);
    if (flags()->isSet(VKLPFlags::OUTBOX)) message->setIsIncoming(false);
    if (flags()->isSet(VKLPFlags::CHAT)) message->setIsChat(true);

    if (needPreviousMessage()) {
        auto handler = new VKHandlerFirstMessage(storage());
        if (isChat()) {
            handler->addChatId(message->chatId());
        } else {
            handler->addUserId(message->chatId());
        }
        storage()->helper()->request(this, handler);

    } else {
        qDebug()<<"dont need message"<<id();
        if (flags()->isSet(VKLPFlags::DELETED)) message->setIsDeleted(true);
        m_valid = true;
        deleteLater();
    }
    message->emitChange();
}
