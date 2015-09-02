#ifndef VKHANDLERUSERS_H
#define VKHANDLERUSERS_H

#include <QObject>
#include <QSqlQuery>
#include "vkabstracthandler.h"
#include "vkcontaineruser.h"

class VKHandlerUsers : public VKAbstractHandler
{
    Q_OBJECT
public:
    explicit VKHandlerUsers(VKStorage *storage, QObject *parent = 0);
    virtual const QNetworkRequest processRequest();
    virtual void processReply(QJsonValue *reply);
    virtual QString name();
    void setUsers(QVector<int> ids);
    void setFields(QString fields);

    Q_INVOKABLE int count();
    Q_INVOKABLE VKContainerUser* getPtr(int i);

    QSharedPointer<VKContainerUser> get(int i);
signals:

public slots:
private:
    QVector<int> m_userIds;
    QString m_fields;
    QVector<QSharedPointer<VKContainerUser>> m_users;
};

#endif // VKHANDLERUSERS_H
