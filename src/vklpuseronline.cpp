#include "vklpuseronline.h"

VKLPUserOnline::VKLPUserOnline(QObject *parent) :
    VKLPAbstract(parent)
{
    m_type = VKLPEventType::USER_ONLINE;
    m_device = 0;
    m_userId = 0;
}

void VKLPUserOnline::fromLP(const QJsonArray &data) {
    m_userId = abs(data.at(1).toInt());
    int type = data.at(2).toInt();
    if (type == 0) {
        type = WEB;
    }
    m_device = type;

    m_valid = true;
}

