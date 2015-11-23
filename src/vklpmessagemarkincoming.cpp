#include "vklpmessagemarkincoming.h"

VKLPMessageMarkIncoming::VKLPMessageMarkIncoming(VKStorage *storage, QObject *parent) :
    VKLPAbstract(storage, parent)
{
    m_type = VKLPEventType::MESSAGE_MARK_READ_INCOMING;
    m_msgIdFrom = 0;
    m_msgIdTo = 0;
}

void VKLPMessageMarkIncoming::fromLP(const QJsonArray &data) {
    m_msgIdFrom = data.at(1).toInt();
    m_msgIdTo = data.at(2).toInt();

    mark();

    m_valid = true;
}

void VKLPMessageMarkIncoming::mark() {
    for (int i=m_msgIdFrom;i<=m_msgIdTo;i++) {
        if (storage()->isContainsMessage(i)) {
            auto message = storage()->getMessageById(i);
            if (message->isIncoming()) {
                message->setIsRead(true);
            }
        }
    }
}

