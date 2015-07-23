#include "vklpcounterupdate.h"

VKLPCounterUpdate::VKLPCounterUpdate(QObject *parent) :
    VKLPAbstract(parent)
{
    m_type = VKLPEventType::COUNTER_UPDATE;
    m_count = 0;
}

void VKLPCounterUpdate::fromLP(const QJsonArray &data) {
    m_count = data.at(1).toInt();
    m_valid = true;
}
