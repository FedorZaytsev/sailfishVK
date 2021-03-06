#include "vklpunreadcount.h"

VKLPUnreadCount::VKLPUnreadCount(VKStorage *storage, QObject *parent) :
    VKLPAbstract(storage, parent)
{
    m_count = 0;
}

void VKLPUnreadCount::fromLP(const QJsonArray &data) {
    m_count = data.at(1).toInt();
}

int VKLPUnreadCount::count() {
    return m_count;
}
