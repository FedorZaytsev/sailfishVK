#include "vklpuseroffline.h"
#include <math.h>

VKLPUserOffline::VKLPUserOffline(QObject *parent) :
    VKLPAbstract(parent)
{
    m_type = VKLPEventType::USER_OFFLINE;
    m_userId = 0;
    m_timeout = false;
}

void VKLPUserOffline::fromLP(const QJsonArray &data) {
    m_userId = abs(data.at(1).toInt());
    m_timeout = data.at(2).toInt();

    m_valid = true;
}
