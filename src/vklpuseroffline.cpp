#include "vklpuseroffline.h"
#include <math.h>

VKLPUserOffline::VKLPUserOffline(VKStorage *storage, QObject *parent) :
    VKLPAbstract(storage, parent)
{
    m_type = VKLPEventType::USER_OFFLINE;
    m_userId = 0;
    m_timeout = false;
}

void VKLPUserOffline::fromLP(const QJsonArray &data) {
    m_userId = abs(data.at(1).toInt());
    m_timeout = data.at(2).toInt();

    if (storage()->isContainsUser(m_userId)) {
        storage()->getUserById(m_userId)->setIsOnline(false);
    }

    deleteLater();
    m_valid = true;
}
