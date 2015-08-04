#include "vklpunreadcount.h"

VKLPUnreadCount::VKLPUnreadCount(QObject *parent) :
    VKLPAbstract(parent)
{
    m_count = 0;
}

void VKLPUnreadCount::fromLP(const QJsonArray &data) {
    m_count = data.at(1).toInt();
}

int VKLPUnreadCount::count() {
    return m_count;
}
