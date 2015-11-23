#ifndef VKUSERTYPING_H
#define VKUSERTYPING_H

#include <QObject>
#include <QTimer>
#include "vkstorage.h"
#include "vkcontaineruser.h"

class VKUserTyping;
class VKUserDescriptor;
class VKUserDescriptor : public QObject
{
    Q_OBJECT
public:
    explicit VKUserDescriptor(QSharedPointer<VKContainerUser> user, u_int32_t time, QObject* parent = 0);
    QString name() const;
    int userId() const;
    void update();
signals:
    void remove(VKUserDescriptor* desc);
private:
    QTimer m_timer;
    QSharedPointer<VKContainerUser> m_user;
};

class VKUserTyping : public QObject
{
    Q_OBJECT
public:
    explicit VKUserTyping(QObject *parent = 0);

    void add(QSharedPointer<VKContainerUser> user, u_int32_t time);
    QString text();
signals:
    void changed();
private:
    QVector<VKUserDescriptor*> m_users;
};

#endif // VKUSERTYPING_H
