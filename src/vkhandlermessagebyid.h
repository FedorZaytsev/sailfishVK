#ifndef VKHANDLERMESSAGEBYID_H
#define VKHANDLERMESSAGEBYID_H
#include "vkabstracthandler.h"
#include "vkcontainermessage.h"

class VKHandlerMessageById : public VKAbstractHandler
{
    Q_OBJECT
public:
    explicit VKHandlerMessageById(VKStorage* storage, QObject *parent = 0);
    virtual const QNetworkRequest processRequest();
    virtual void processReply(QJsonValue *_reply);
    virtual QString name();
    virtual void merge(VKAbstractHandler* handler);

    QVector<int> messageIds();
    void add(int id);
signals:

public slots:
private:
    QVector<int> m_messageIds;
};

#endif // VKHANDLERMESSAGEBYID_H
