#ifndef VKHANDLERMARKASREAD_H
#define VKHANDLERMARKASREAD_H

#include "vkabstracthandler.h"

class VKHandlerMarkAsRead : public VKAbstractHandler
{
    Q_OBJECT
public:
    explicit VKHandlerMarkAsRead(VKStorage* storage, QObject *parent = 0);
    virtual const QNetworkRequest processRequest();
    virtual void processReply(QJsonValue *reply);
    virtual QString name() {return "markAsRead";}

    void setMsgs(QList<int> lst);

    Q_INVOKABLE int count() { return m_ids.size(); }
    Q_INVOKABLE int get(int i) { return m_ids.at(i); }

signals:

public slots:
private:
    QList<int> m_ids;

};

#endif // VKHANDLERMARKASREAD_H
