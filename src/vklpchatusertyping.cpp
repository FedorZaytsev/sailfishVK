#include "vklpchatusertyping.h"
#include "vkcontainermessage.h"

VKLPChatUserTyping::VKLPChatUserTyping(VKStorage *storage, QObject *parent) :
    VKLPUserTyping(storage, parent)
{
    m_type = VKLPEventType::CHAT_USER_TYPING;
}

int VKLPChatUserTyping::parseChatId(int id) {
    return MAX_USER_ID + id;
}
