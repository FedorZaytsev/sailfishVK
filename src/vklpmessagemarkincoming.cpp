#include "vklpmessagemarkincoming.h"

VKLPMessageMarkIncoming::VKLPMessageMarkIncoming(QObject *parent) :
    VKLPAbstract(parent)
{
    m_type = VKLPEventType::MESSAGE_MARK_READ_INCOMING;
    m_userId = 0;
    m_isChat = false;
    m_msgId = 0;
}

void VKLPMessageMarkIncoming::fromLP(const QJsonArray &data) {
    setUserId(data.at(1).toInt());
    m_msgId = data.at(2).toInt();

    m_valid = true;
}


void VKLPMessageMarkIncoming::setUserId(int id) {
    m_userId = id > 2000000000 ? id - 2000000000 : id;
    m_isChat = id > 2000000000;
}
