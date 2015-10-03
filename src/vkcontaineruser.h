#ifndef VKCONTAINERUSER_H
#define VKCONTAINERUSER_H

#include <QObject>
#include <QJsonObject>
#include "vkstorage.h"
#include "vkabstractcontainer.h"

class VKContainerUser;
class VKStorage;
class VKContainerUser : public VKAbstractContainer
{
    Q_OBJECT
public:
    explicit VKContainerUser(QObject *parent = 0);
    ~VKContainerUser();

    static QSharedPointer<VKContainerUser> fromJson(VKStorage *storage, const QJsonObject &obj);

    Q_INVOKABLE int id() const              { return m_id; }
    Q_INVOKABLE QString firstName() const   { return m_firstName; }
    Q_INVOKABLE QString lastName() const    { return m_lastName; }
    Q_INVOKABLE QString iconSmall() const   { return m_iconSmall; }
    Q_INVOKABLE QString iconMedium() const  { return m_iconMedium; }
    Q_INVOKABLE QString iconLarge() const   { return m_iconLarge; }
    Q_INVOKABLE bool isOnline() const       { return m_online; }
    Q_INVOKABLE bool isValid() const        { return m_valid; }
    Q_INVOKABLE QString userName() const;

    void setId(int arg);
    void setFirstName(QString arg);
    void setLastName(QString arg);
    void setIconSmall(QString arg);
    void setIconMedium(QString arg);
    void setIconLarge(QString arg);
    void setIsOnline(bool arg);
    void valid(bool b)                      { m_valid = b; }
private:
    int m_id;
    QString m_firstName;
    QString m_lastName;
    QString m_iconSmall;
    QString m_iconMedium;
    QString m_iconLarge;
    bool m_online;
    bool m_valid;
};


#endif // VKCONTAINERUSER_H
