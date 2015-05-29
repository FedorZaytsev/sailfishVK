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
    //virtual void processReply(QJsonObject*);
    //virtual QString name();
    void setUsers(QVector<int> ids);
signals:

public slots:
private:
    QSet<int> m_users;
};

#endif // VKHANDLERUSERS_H
