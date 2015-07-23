#include "vklpmessageflagsreset.h"

VKLPMessageFlagsReset::VKLPMessageFlagsReset(QObject *parent) :
    VKLPMessageFlagsSet(parent)
{
    m_type = VKLPEventType::MESSAGE_FLAGS_RESET;
}
