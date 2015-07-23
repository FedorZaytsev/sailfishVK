#include "vklpabstract.h"

VKLPAbstract::VKLPAbstract(QObject *parent) :
    QObject(parent)
{
    m_valid = false;
    m_type = VKLPEventType::INVALID;
}

void VKLPAbstract::complete(QVector<VKContainerDialog *> , QVector<VKContainerMessage *> , QVector<VKContainerUser *> ) {
}
