#ifndef VKHANDLERDIALOGBYID_H
#define VKHANDLERDIALOGBYID_H

#include "vkabstracthandler.h"

class VKHandlerDialogById : public VKAbstractHandler
{
    Q_OBJECT
public:
    explicit VKHandlerDialogById(VKStorage* storage, QObject *parent = 0);
    virtual const QNetworkRequest processRequest();
    virtual void processReply(QJsonValue *_reply);
    virtual QString name();
    virtual void merge(VKAbstractHandler* handler);

    void add(int id);
    QVector<int> messageIds();
signals:

public slots:
private:
    QVector<int> m_messageIds;
};

#endif // VKHANDLERDIALOGBYID_H
