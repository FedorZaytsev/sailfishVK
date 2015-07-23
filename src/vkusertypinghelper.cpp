#include "vkusertypinghelper.h"

VKUserTypingHelper::VKUserTypingHelper(QObject *parent) :
    QObject(parent)
{
    qDebug()<<"created";
    m_timer.setInterval(1000);
    m_timer.stop();
    QObject::connect(&m_timer, &QTimer::timeout, this, &VKUserTypingHelper::timeout);
}

void VKUserTypingHelper::addUser(QString user) {
    qDebug()<<"adding user"<<user;
    if (!m_users.size()) {
        qDebug()<<"timer started";
        m_timer.start();
    }
    m_users[user] = QDateTime::currentDateTime().addSecs(TYPING_SECS_COUNT);
    //m_users.push_back({user, QDateTime::currentDateTime().addSecs(TYPING_SECS_COUNT)});
    qDebug()<<"ready";
}

void VKUserTypingHelper::calculateString() {
    QString str;
    auto keys = m_users.keys();
    switch (keys.size()) {
    case 0:
        str = "";
        break;
    case 1:
        str = keys[0] + " is typing...";
        break;
    case 2:
        str = keys[0] + " and " + keys[1] + " are typing...";
        break;
    default:
        str = keys[0] + ", " + keys[1] + " and others are typing...";
    }
    if (str != m_string) {
        m_string = str;
        qDebug()<<"string updated"<<str;
        emit textUpdated(str);
    }
}

void VKUserTypingHelper::timeout() {
    //todo delete

    QList<QString> toDelete;
    auto time = QDateTime::currentDateTime();
    for ( auto e : m_users.keys() ) {
        if (m_users[e] < time) {
            qDebug()<<"removing user"<<e;
            toDelete.append( e );

        }
    }

    for(auto e : toDelete) {
        m_users.remove(e);
    }

    if (!m_users.size()) {
        qDebug()<<"no more users, timer stopped";
        m_timer.stop();
    }
    calculateString();
}


