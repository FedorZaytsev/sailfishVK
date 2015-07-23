#include "vklpmessageflagsset.h"

VKLPMessageFlagsSet::VKLPMessageFlagsSet(QObject *parent) :
    VKLPMessageFlagsChange(parent)
{
    m_type = VKLPEventType::MESSAGE_FLAGS_SET;
    m_message = NULL;
}

void VKLPMessageFlagsSet::fromLP(const QJsonArray &data, QList<QString> &l) {
    super::fromLP(data);

    if (flags()->isSet(VKLPFlags::DELETED)) {
        l.push_back(QString::number(id()));
        return;
    }
    m_valid = !flags()->isSet(VKLPFlags::DELETED);
}

void VKLPMessageFlagsSet::complete(QVector<VKContainerDialog*>, QVector<VKContainerMessage*> messages, QVector<VKContainerUser*>) {
    qDebug()<<"requesting"<<id();
    for (auto e : messages) {
        if (e->msgId() == id()) {
            m_message = e;
            m_valid = true;
            break;
        }
    }
}
