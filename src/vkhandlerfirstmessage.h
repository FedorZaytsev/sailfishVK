#ifndef VKHANDLERFIRSTMESSAGE_H
#define VKHANDLERFIRSTMESSAGE_H

#include "vkabstracthandler.h"
#include "vkhandlermessages.h"

class VKHandlerFirstMessage : public VKAbstractHandler
{
    Q_OBJECT
public:
    explicit VKHandlerFirstMessage(VKStorage* storage, QObject *parent = 0);
    virtual const QNetworkRequest processRequest();
    virtual void processReply(QJsonValue *reply);
    virtual QString name();
    virtual void merge(VKAbstractHandler* handler);

    void addUserId(int id);
    void addChatId(int id);
    QVector<int> chatIds();
signals:

public slots:
private:
    QVector<int> m_chatIds;
};

#endif // VKHANDLERFIRSTMESSAGE_H
