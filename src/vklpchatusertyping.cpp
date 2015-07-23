#include "vklpchatusertyping.h"

VKLPChatUserTyping::VKLPChatUserTyping(QObject *parent) :
    VKLPUserTyping(parent)
{
    m_type = VKLPEventType::CHAT_USER_TYPING;
}
