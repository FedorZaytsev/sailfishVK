#include "vklpmessagenew.h"

VKLPMessageNew::VKLPMessageNew(QObject *parent) :
    VKLPAbstract(parent)
{
    m_id = 0;
    m_isChat = false;
    m_userId = 0;
    m_type = VKLPEventType::MESSAGE_NEW;
}

void VKLPMessageNew::fromLP(const QJsonArray &data, QList<QString> &msgs, QList<QString> &users, QList<QString> &chats) {

    m_id = data.at(1).toInt();
    msgs.append(QString::number(m_id));
    int fromId = data.at(3).toInt();
    if (fromId < MAX_USER_ID) {
        m_userId = fromId;
        m_isChat = false;
        users.append(QString::number(m_userId));
    } else {
        m_userId = fromId - MAX_USER_ID;
        chats.append(QString::number(m_userId));
    }
    QJsonObject attachments = data.at(7).toObject();


    if (!attachments.value("from").isNull()) {
        auto fromUser = attachments.value("from").toString();
        users.append(fromUser);
    }

    if (attachments.value("fwd").isString()) {
        VKLongPollUpdateParser parser;
        parser.parse(attachments.value("fwd").toString());

        users.append(parser.uniqueUsers());
    }

    m_valid = false;
}

void VKLPMessageNew::complete(QVector<QSharedPointer<VKContainerDialog>> dialogs, QVector<QSharedPointer<VKContainerMessage>> messages, QVector<QSharedPointer<VKContainerUser>> users) {
    Q_UNUSED(messages);
    Q_UNUSED(users);

    qDebug()<<"requesting"<<id();
    for (auto e : dialogs) {
        if (e->message()->msgId() == id()) {
            qDebug()<<"found requested";
            m_dialog = e;
            m_valid = true;
            break;
        }
    }
}
