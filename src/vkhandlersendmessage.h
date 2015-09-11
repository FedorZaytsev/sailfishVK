#ifndef VKHANDLERSENDMESSAGE_H
#define VKHANDLERSENDMESSAGE_H

#include "vkabstracthandler.h"

class VKHandlerSendMessage : public VKAbstractHandler
{
    Q_OBJECT
public:
    explicit VKHandlerSendMessage(VKStorage* storage, QObject *parent = 0);
    virtual const QNetworkRequest processRequest();
    virtual void processReply(QJsonValue *reply);
    virtual QString name();


    void        setUserId(int arg)              { m_userId = arg; }
    void        setIsChat(int arg)              { m_isChat = arg; }
    void        setText(QString arg)            { m_text = arg; }
    void        setForward(QString arg)         { m_forward = arg; }
    void        setAttachments(QString arg)     { m_attachments = arg; }
    void        setGuid(int arg)                { m_guid = arg; }

    Q_INVOKABLE int id()                        { return m_messageId; }
    Q_INVOKABLE int guid()                      { return m_guid; }

signals:

public slots:
private:
    int m_userId;
    bool m_isChat;
    int m_guid;
    QString m_text;
    QString m_forward;
    QString m_attachments;
    int m_messageId;
};

#endif // VKHANDLERSENDMESSAGE_H
