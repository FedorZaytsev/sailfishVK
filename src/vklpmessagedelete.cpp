#include "vklpmessagedelete.h"

VKLPMessageDelete::VKLPMessageDelete(QObject *parent) :
    VKLPAbstract(parent)
{
    m_id = 0;
    m_userId = 0;
    m_isChat = false;
    m_message = NULL;
    m_type = VKLPEventType::MESSAGE_DELETE;
}

void VKLPMessageDelete::fromLP(const QJsonArray &data, QList<QString> &l) {
    setId(data.at(1).toInt());
    l.push_back(QString::number(id()));
    if (data.count() > 2) {
        setUserId(data.at(2).toInt());
    }
    m_valid = false;
}

void VKLPMessageDelete::complete(QVector<VKContainerDialog*> , QVector<VKContainerMessage*> messages, QVector<VKContainerUser *> ) {
    qDebug()<<"requesting"<<id();
    for (auto e : messages) {
        if (e->msgId() == id()) {
            m_message = e;
            m_valid = true;
            break;
        }
    }
}

void VKLPMessageDelete::setUserId(int id) {
    m_userId = id > 2000000000 ? id - 2000000000 : id;
    m_isChat = id > 2000000000;
}
