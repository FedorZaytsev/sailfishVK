#ifndef VKHANDLERMESSAGES_H
#define VKHANDLERMESSAGES_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>
#include "vkcontainermessage.h"
#include "vkabstracthandler.h"

class VKHandlerMessages : public VKAbstractHandler
{
    Q_OBJECT
public:
    explicit VKHandlerMessages(VKStorage* storage, QObject *parent = 0);
    virtual const QNetworkRequest processRequest();
    virtual void processReply(QJsonValue *_reply);
    virtual QString name();
    void setOffset(int offset);
    void setCount(int count);
    void setUserId(int id);
    void setChatId(int id);
    void setStartMessageId(int id);
    void setReverse(bool rev);

    Q_INVOKABLE int offset() { return m_offset; }
    Q_INVOKABLE int count() { return m_count; }
    Q_INVOKABLE int unreadCount() { return m_unreadCount; }

signals:

public slots:
private:
    int m_offset;
    int m_count;
    int m_recievedCount;
    int m_id;
    int m_unreadCount;
    bool m_isChat;
    int m_startMsgId;
    bool m_reverse;
};

#endif // VKHANDLERMESSAGES_H
