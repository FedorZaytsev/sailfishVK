#ifndef VKHANDLERUSERS_H
#define VKHANDLERUSERS_H

#include <QObject>
#include <QSet>
#include "vkabstracthandler.h"
#include "vkcontaineruser.h"

class VKHandlerUsers;
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
    QVector<int> users();
    QString fields();

    void merge(VKAbstractHandler *handler);
private:
    QString mergeFields(QString f1, QString f2);
signals:

public slots:
private:
    QVector<int> m_userIds;
    QString m_fields;
};

#endif // VKHANDLERUSERS_H
