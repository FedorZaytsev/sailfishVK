#include "vklpmessagemarkoutcoming.h"

VKLPMessageMarkOutcoming::VKLPMessageMarkOutcoming(VKStorage *storage, QObject *parent) :
    VKLPMessageMarkIncoming(storage, parent)
{
    m_type = VKLPEventType::MESSAGE_MARK_READ_OUTCOMING;
}

void VKLPMessageMarkOutcoming::mark() {
    for (int i=m_msgIdFrom;i<=m_msgIdTo;i++) {
        if (storage()->isContainsMessage(i)) {
            auto message = storage()->getMessageById(i);
            if (!message->isIncoming()) {
                message->setIsRead(true);
            }
        }
    }
}
