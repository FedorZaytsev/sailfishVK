#include "vklpmessageflagsreset.h"
#include "vkhandlermessagebyid.h"
#include "vkhandlerdialogbyid.h"

VKLPMessageFlagsReset::VKLPMessageFlagsReset(VKStorage *storage, QObject *parent) :
    VKLPMessageFlagsSet(storage, parent)
{
    m_type = VKLPEventType::MESSAGE_FLAGS_RESET;
}

void VKLPMessageFlagsReset::completed() {
    Q_ASSERT(!m_valid);
    Q_ASSERT(storage()->isContainsMessage(id()));
    auto message = storage()->getMessageById(id());

    message->setIsDeleted(false);
    if (flags()->isSet(VKLPFlags::UNREAD)) message->setIsRead(true);
    if (flags()->isSet(VKLPFlags::OUTBOX)) message->setIsIncoming(true);
    if (flags()->isSet(VKLPFlags::CHAT)) message->setIsChat(false);

    message->emitChange();
    deleteLater();
}

bool VKLPMessageFlagsReset::needPreviousMessage() {

    qDebug()<<(flags()->isSet(VKLPFlags::DELETED) && !storage()->isContainsMessage(id()));

    return flags()->isSet(VKLPFlags::DELETED) && !storage()->isContainsMessage(id());
}

void VKLPMessageFlagsReset::process() {

    qDebug()<<"Flags:";
    flags()->print();

    if (needPreviousMessage()) {
        qDebug()<<"requesting message before"<<id();
        auto handler = new VKHandlerMessageById(storage());
        handler->add(id());
        storage()->helper()->request(this, handler);

        //we need dialog when user is trying to recover messages from dialog
        //which was previously deleted
        if (!storage()->isContainsDialog(userId())) {
            auto hdialogs = new VKHandlerDialogById(storage());
            hdialogs->add(id());
            storage()->helper()->request(nullptr, hdialogs);
        }

    } else {

        if (!storage()->isContainsMessage(id())) {
            qDebug()<<"doesn't contains message, chat id"<<userId();

            if (storage()->isContainsDialog(userId())) {
                qDebug()<<"decreasing unread count";
                auto dialog = storage()->getDialogById(userId());
                dialog->setUnreadCount( dialog->unreadCount() - 1);
            }

            m_valid = true;
            deleteLater();
            return;
        }

        auto message = storage()->getMessageById(id());
        if (flags()->isSet(VKLPFlags::UNREAD)) message->setIsRead(true);
        if (flags()->isSet(VKLPFlags::OUTBOX)) message->setIsIncoming(true);
        if (flags()->isSet(VKLPFlags::CHAT)) message->setIsChat(false);

        if (flags()->isSet(VKLPFlags::DELETED)) {
            qDebug()<<"set message is deleted false"<<message->body().mid(0,10);
            message->setIsDeleted(false);
        }
        qDebug()<<"emit message change";
        message->emitChange();
        m_valid = true;
        deleteLater();
    }


}
