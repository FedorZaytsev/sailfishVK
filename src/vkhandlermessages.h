#ifndef VKHANDLERMESSAGES_H
#define VKHANDLERMESSAGES_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>
#include "vkcontainermessage.h"
#include "vkabstracthandler.h"
#include "vkhandlerusers.h"
#include "vkcontainerphoto.h"

class VKHandlerMessages : public VKAbstractHandler
{
    Q_OBJECT
public:
    explicit VKHandlerMessages(VKStorage* storage, QObject *parent = 0);
    virtual const QNetworkRequest processRequest();
    virtual void processReply(QJsonValue *reply);
    virtual QString name();
    void setOffset(int offset);
    void setCount(int count);
    void setUserId(int id);
    void setChatId(int id);
    void setStartMessageId(int id);
    void setReverse(bool rev);

    Q_INVOKABLE int count();
    Q_INVOKABLE VKContainerMessage* get(int i);

signals:

public slots:
    void usersUpdateData();
private:
    int m_offset;
    int m_count;
    int m_id;
    bool m_isChat;
    int m_startMsgId;
    bool m_reverse;

    QVector<VKContainerMessage*> m_messages;
    VKHandlerUsers* m_usersHandler;
};

#endif // VKHANDLERMESSAGES_H
