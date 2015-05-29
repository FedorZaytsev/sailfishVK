#ifndef VKDIALOGCONTAINER_H
#define VKDIALOGCONTAINER_H

#include <QObject>
#include <QVariantList>
#include <QVariant>
#include <QDateTime>
#include <QSqlQuery>
#include <QJsonObject>
#include <QJsonArray>
#include "vkabstractcontainer.h"

class VKContainerUser;
class VKContainerMessage;
class VKStorage;

class VKContainerMessage : public VKAbstractContainer
{
    Q_OBJECT

public:
    explicit VKContainerMessage(QObject *parent = 0);
             ~VKContainerMessage();

    static VKContainerMessage* fromJson(VKStorage* storage, QJsonObject obj, const QJsonArray users);
    static VKContainerMessage* fromSql(VKStorage *storage, QSqlQuery& query);

    Q_INVOKABLE int msgId() const                   { return m_msgId; }
    Q_INVOKABLE QDateTime date() const              { return m_date; }
    Q_INVOKABLE bool isIncoming() const             { return m_isIncoming; }
    Q_INVOKABLE VKContainerUser* user() const       { return m_user; }
    Q_INVOKABLE bool readState() const              { return m_readState; }
    Q_INVOKABLE QString body() const                { return m_body; }
    Q_INVOKABLE bool isChat() const                 { return m_isChat; }
    Q_INVOKABLE int chatId() const                  { return m_chatId; }

    void setMsgId(int arg) { m_msgId = arg; }
    void setDate(QDateTime arg) { m_date = arg; }
    void setIsIncoming(bool arg) { m_isIncoming = arg; }
    void setReadState(bool arg) { m_readState = arg; }
    void setBody(QString arg) { m_body = arg; }
    void setIsChat(bool arg) { m_isChat = arg; }
    void setChatId(int arg) { m_chatId = arg; }
    void setUser(VKContainerUser* arg);

private:
    int                     m_msgId;
    QDateTime               m_date;
    bool                    m_isIncoming;       //optimaze bool flags
    bool                    m_readState;
    bool                    m_isChat;
    VKContainerUser*        m_user;
    QString                 m_body;
    int                     m_chatId;
};


#endif // VKDIALOGCONTAINER_H
