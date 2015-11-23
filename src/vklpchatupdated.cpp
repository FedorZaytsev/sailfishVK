#include "vklpchatupdated.h"

VKLPChatUpdated::VKLPChatUpdated(VKStorage *storage, QObject *parent) :
    VKLPAbstract(storage, parent)
{
    m_chatId = 0;
    m_byUser = false;
}

void VKLPChatUpdated::fromLP(const QJsonArray &data) {
    m_chatId = data.at(1).toInt();
    m_byUser = data.at(2).toInt();
    m_valid = true;
}
