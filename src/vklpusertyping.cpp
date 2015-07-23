#include "vklpusertyping.h"

VKLPUserTyping::VKLPUserTyping(QObject *parent) :
    VKLPAbstract(parent)
{
    m_type = VKLPEventType::USER_TYPING;
    m_id = 0;
    m_chatId = 0;
}

void VKLPUserTyping::fromLP(const QJsonArray &data, QList<QString> &l) {

    m_id = data.at(1).toInt();
    m_chatId = data.at(2).toInt();

    l.push_back(QString::number(id()));

    m_valid = false;
}

void VKLPUserTyping::complete(QVector<VKContainerDialog*>, QVector<VKContainerMessage*>, QVector<VKContainerUser *> users) {
    qDebug()<<"requesting"<<id();
    for (auto e: users) {
        if (e->id() == m_id) {
            m_userName = e->firstName() + " " + e->lastName();
            m_valid = true;
            return;
        }
    }
}

