#include "vklpmessageflagschange.h"

VKLPMessageFlagsChange::VKLPMessageFlagsChange(QObject *parent) :
    VKLPAbstract(parent)
{
    m_id = 0;
    m_flags = NULL;
    m_userId = 0;
    m_isChat = false;
    m_type = VKLPEventType::MESSAGE_FLAGS_CHANGE;
}

void VKLPMessageFlagsChange::fromLP(const QJsonArray &data) {
    setId(data.at(1).toInt());
    setFlags(new VKLPFlags(data.at(2).toInt()));
    if (data.count() > 2) {
        setUserId(data.at(3).toInt());
    }
    m_valid = true;
}

void VKLPMessageFlagsChange::setFlags(VKLPFlags *flags) {
    Q_ASSERT(flags);
    m_flags = flags;
    m_flags->setParent(this);

}

void VKLPMessageFlagsChange::setUserId(int id) {
    m_userId = id > 2000000000 ? id - 2000000000 : id;
    m_isChat = id > 2000000000;
}
