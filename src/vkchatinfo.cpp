#include "vkchatinfo.h"

VKChatInfo::VKChatInfo(QObject *parent) :
    QObject(parent)
{
    Q_ASSERT(0);
}

bool VKChatInfo::isChat() const {
    return m_isChat;
}

int VKChatInfo::userId() const {
    return m_userId;
}

int VKChatInfo::chatId() const {
    return m_chatId;
}

QVector<int> VKChatInfo::activeMemberIds() const {
    return m_activeMemberIds;
}

int VKChatInfo::adminId() const {
    return m_adminId;
}

void VKChatInfo::parseChatInfo(QJsonObject &message) {
    Q_UNUSED(message);
    qDebug()<<"VKChatInfo::parseChatInfo not implemented";
}

