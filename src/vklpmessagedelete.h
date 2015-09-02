#ifndef VKLPMESSAGEDELETE_H
#define VKLPMESSAGEDELETE_H

#include "vklpabstract.h"
#include "vklpeventtype.h"
#include "vkcontainermessage.h"

class VKLPMessageDelete : public VKLPAbstract
{
    Q_OBJECT
public:
    explicit VKLPMessageDelete(QObject *parent = 0);
    void fromLP(const QJsonArray &data, QList<QString> &l);
    virtual void complete(QVector<QSharedPointer<VKContainerDialog>> dialogs, QVector<QSharedPointer<VKContainerMessage>> messages, QVector<QSharedPointer<VKContainerUser>> users);


                void                    setId(int arg)                  { m_id = arg; }
    Q_INVOKABLE int                     id()                            { return m_id; }
                void                    setUserId(int id);
    Q_INVOKABLE int                     userId()                        { return m_userId; }
    Q_INVOKABLE bool                    isChat()                        { return m_isChat; }
    Q_INVOKABLE VKContainerMessage*     messagePtr()                    { return m_message.data(); }
    QSharedPointer<VKContainerMessage>  message()                       { return m_message; }
signals:

public slots:
private:
    int m_id;
    QSharedPointer<VKContainerMessage> m_message;
    int m_userId;
    bool m_isChat;
};

#endif // VKLPMESSAGEDELETE_H
