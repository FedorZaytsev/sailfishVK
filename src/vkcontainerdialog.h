#ifndef VKDIALOGHANDLER_H
#define VKDIALOGHANDLER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QSharedPointer>
#include <QDateTime>
#include "vkabstractcontainer.h"
#include "vkusertyping.h"

class VKContainerUser;
class VKContainerMessage;
class VKContainerChatIcon;
class VKContainerDialog : public VKAbstractContainer
{
    Q_OBJECT

public:
    explicit VKContainerDialog(VKStorage *storage, QObject *parent = 0);
             ~VKContainerDialog();
    static QSharedPointer<VKContainerDialog>           fromJson(VKStorage *storage, QJsonObject obj, const QJsonArray users);

    Q_INVOKABLE int                     unreadCount() const                    { return m_unreadCount; }
    Q_INVOKABLE int                     id() const                             { return m_id; }
    Q_INVOKABLE bool                    isChat() const                         { return m_isChat; }
    Q_INVOKABLE QString                 chatName() const                       { return m_chatName; }
    Q_INVOKABLE QDateTime               date() const;

    QSharedPointer<VKContainerMessage>  firstMessage() const;
    int                                 messagesCount() const                  { return m_messages.size(); }
    QSharedPointer<VKContainerMessage>  getMessageByIndex(int idx) const;
    QSharedPointer<VKContainerMessage>  getMessageById(int id) const;
    void                                removeMessage(int idx);
    int                                 appendMessage(QSharedPointer<VKContainerMessage> msg);
    QSharedPointer<VKContainerMessage>  findMessage(int id) const;
    QSharedPointer<VKContainerChatIcon> chatIcon() const;

    bool                                isDeleted() const ;

    void                                setUnreadCount(int arg);
    void                                setId(int arg);
    void                                setIsChat(bool arg);
    void                                setChatName(QString arg);
    void                                setChatIcon(QSharedPointer<VKContainerChatIcon> arg);
    void                                addUserTyping(QSharedPointer<VKContainerUser> user, u_int32_t time = 5*1000);

    QString debugDescription();

    bool updateFrom(QSharedPointer<VKContainerDialog> dialog);
    virtual void completed();

private:
    int insertSorted(QSharedPointer<VKContainerMessage> message);
    void removeSorted(int idx);
signals:
    void unreadCountChanged(int count);
    void idChanged(int id);
    void isChatChanged(bool b);
    void chatNameChanged(QString name);
    void dialogDeleted(VKContainerDialog* dialog);
public slots:
    void onMessageChanged(VKAbstractContainer* message);
    void onMessageDeleted(VKContainerMessage* message);
private:
    int                                             m_unreadCount;
    QVector<QSharedPointer<VKContainerMessage>>     m_messagesSorted;
    QMap<int, QSharedPointer<VKContainerMessage>>   m_messages;
    int                                             m_id;
    bool                                            m_isChat;
    QString                                         m_chatName;
    QSharedPointer<VKContainerChatIcon>             m_chatIcon;
    VKUserTyping*                                   m_typingUsers;
};


#endif // VKDIALOGHANDLER_H
