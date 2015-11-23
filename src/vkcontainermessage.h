#ifndef VKDIALOGCONTAINER_H
#define VKDIALOGCONTAINER_H

#include <QObject>
#include <QVariantList>
#include <QVariant>
#include <QVector>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>
#include "vkabstractcontainer.h"
#include "vkcontainerattachments.h"

#define MAX_USER_ID 2000000000

class VKContainerUser;
class VKContainerMessage;
class VKStorage;
class VKHandlerUsers;
class VKContainerMessageAction;
class VKContainerMessage : public VKAbstractContainer
{
    Q_OBJECT

public:
    explicit VKContainerMessage(VKStorage *storage, QObject *parent = 0);
    virtual ~VKContainerMessage();

    static QSharedPointer<VKContainerMessage> fromJson(VKStorage* storage, QJsonObject obj, const QJsonArray users);
    virtual void completed();

    Q_INVOKABLE int id() const                                      { return m_id; }
    Q_INVOKABLE QDateTime date() const                              { return m_date; }
    Q_INVOKABLE bool isIncoming() const                             { return m_isIncoming; }
    Q_INVOKABLE bool isRead() const;
    Q_INVOKABLE QString body() const                                { return m_body; }
    Q_INVOKABLE bool isChat() const                                 { return m_isChat; }
    Q_INVOKABLE int chatId() const                                  { return m_chatId; }
    Q_INVOKABLE bool isDeleted() const                              { return m_isDeleted; }

    Q_INVOKABLE int countFwd();


    QSharedPointer<VKContainerUser> user() const;
    QSharedPointer<VKContainerAttachments> attachments() const;
    QSharedPointer<VKContainerMessageAction> action() const;
    QSharedPointer<VKContainerMessage> getFwd(int i) const;

    void setId(int arg);
    void setDate(QDateTime arg);
    void setIsIncoming(bool arg);
    void setBody(QString arg);
    void setIsChat(bool arg);
    void setChatId(int arg);
    void setIsDeleted(bool arg);
    void setUser(QSharedPointer<VKContainerUser> arg);
    void addFwdMsg(QSharedPointer<VKContainerMessage> arg);
    void setFwdMsg(int pos, QSharedPointer<VKContainerMessage> arg);
    void clearFwd();
    void setAttachments(QSharedPointer<VKContainerAttachments> attachments);
    void setAction(QSharedPointer<VKContainerMessageAction> action);
    void setIsRead(bool arg);

    static void processEmoji(QString &s);
    void createTemplateDialog();
    bool updateFrom(QSharedPointer<VKContainerMessage> message);

    QString debugDescription();

    enum ReadState {
        UNKNOWN = 0,
        READ,
        UNREAD
    };
signals:
    void deleted(VKContainerMessage* msg);
    void unreadChanged();
private:
    int                                         m_id;
    QDateTime                                   m_date;
    bool                                        m_isIncoming;       //optimaze bool flags
    int                                         m_readState;
    bool                                        m_isChat;
    bool                                        m_isDeleted;
    QSharedPointer<VKContainerUser>             m_user;
    QString                                     m_body;
    int                                         m_chatId;
    QVector<QSharedPointer<VKContainerMessage>> m_fwd;
    QSharedPointer<VKContainerAttachments>      m_attachments;
    QSharedPointer<VKContainerMessageAction>    m_action;

};


#endif // VKDIALOGCONTAINER_H
