#include "vkusertyping.h"

VKUserTyping::VKUserTyping(QObject *parent) :
    QObject(parent)
{
}

void VKUserTyping::add(QSharedPointer<VKContainerUser> user, u_int32_t time) {
    for (auto e: m_users) {
        if (e->userId() == user->id()) {
            e->update();
            emit changed();
            return;
        }
    }

    //if not found;
    auto desc = new VKUserDescriptor(user, time);
    QObject::connect(desc, &VKUserDescriptor::remove, [this](VKUserDescriptor* desc) {
        for (int i=0;i<m_users.length();i++) {
            if (m_users[i] == desc) {
                qDebug()<<"removing user"<<m_users[i]->name();
                m_users.remove(i);
                desc->deleteLater();
                emit changed();
                return;
            }
        }
        Q_ASSERT(0);
    });
}

QString VKUserTyping::text() {
    switch(m_users.size()) {
    case 0:
        return "";
    case 1:
        return QString("%1 is typing").arg(m_users[0]->name());
    default:
        return QString("%1 and ... are typing").arg(m_users[0]->name());

    }
}


VKUserDescriptor::VKUserDescriptor(QSharedPointer<VKContainerUser> user, u_int32_t time, QObject *parent) :
    QObject(parent)
{
    m_user = user;
    qDebug()<<"time"<<time;
    m_timer.start(time);
    QObject::connect(&m_timer, &QTimer::timeout, [this](){
        emit remove(this);
    });
}

QString VKUserDescriptor::name() const {
    return m_user->userName();
}

int VKUserDescriptor::userId() const {
    return m_user->id();
}

void VKUserDescriptor::update() {
    qDebug()<<"updating user"<<m_user->userName();
    m_timer.start(5*1000);
}
