#include "vklpmessagemarkoutcoming.h"

VKLPMessageMarkOutcoming::VKLPMessageMarkOutcoming(QObject *parent) :
    VKLPMessageMarkIncoming(parent)
{
    m_type = VKLPEventType::MESSAGE_MARK_READ_OUTCOMING;
}
