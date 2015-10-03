#ifndef VKDIALOGHANDLER_H
#define VKDIALOGHANDLER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QSharedPointer>
#include <QDateTime>
#include "vkabstractcontainer.h"

class VKHandlerUsers;
class VKStorage;
class VKContainerMessage;
class VKContainerChatIcon;
class VKContainerDialog : public VKAbstractContainer
{
    Q_OBJECT

public:
    explicit VKContainerDialog(QObject *parent = 0);
             ~VKContainerDialog();
    static QSharedPointer<VKContainerDialog>           fromJson(VKStorage *storage, QJsonObject obj, const QJsonArray users, QVector<int> &userIds);
    virtual void complete(VKAbstractHandler* users);

    Q_INVOKABLE int                     unreadCount() const                    { return m_unreadCount; }
    Q_INVOKABLE int                     id() const                             { return m_id; }
    Q_INVOKABLE bool                    isChat() const                         { return m_isChat; }
    Q_INVOKABLE QString                 chatName() const                       { return m_chatName; }
    Q_INVOKABLE QDateTime               date() const;
    Q_INVOKABLE VKContainerChatIcon*    chatIconPtr() const                    { return m_chatIcon.data(); }
    Q_INVOKABLE VKContainerMessage*     messagePtr() const                     { return m_message.data(); }

    QSharedPointer<VKContainerMessage>  message() const                        { return m_message; }
    QSharedPointer<VKContainerChatIcon> chatIcon() const                       { return m_chatIcon; }

    void                                setUnreadCount(int arg);
    void                                setId(int arg);
    void                                setIsChat(bool arg);
    void                                setChatName(QString arg);
    void                                setChatIcon(QSharedPointer<VKContainerChatIcon> arg);
    void                                setMessage(QSharedPointer<VKContainerMessage> arg);
signals:
    void unreadCountChanged(int count);
    void idChanged(int id);
    void isChatChanged(bool b);
    void chatNameChanged(QString name);

private:
    int                                 m_unreadCount;
    QSharedPointer<VKContainerMessage>  m_message;
    int                                 m_id;
    bool                                m_isChat;
    QString                             m_chatName;
    QSharedPointer<VKContainerChatIcon> m_chatIcon;
};


#endif // VKDIALOGHANDLER_H
