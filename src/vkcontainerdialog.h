#ifndef VKDIALOGHANDLER_H
#define VKDIALOGHANDLER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QSqlQuery>
#include "vkabstractcontainer.h"

class VKStorage;
class VKContainerMessage;
class VKContainerChatIcon;
class VKContainerDialog : public VKAbstractContainer
{
    Q_OBJECT

public:
    explicit VKContainerDialog(QObject *parent = 0);
             ~VKContainerDialog();
    static VKContainerDialog*           fromJson(VKStorage *storage, QJsonObject obj, const QJsonArray users, QVector<int> userIds = QVector<int>());
    static VKContainerDialog*           fromSql(VKStorage *storage, QSqlQuery query);

    Q_INVOKABLE int                     unreadCount() const                    { return m_unreadCount; }
    Q_INVOKABLE VKContainerMessage*     message() const                        { return m_message; }
    Q_INVOKABLE int                     chatId() const                         { return m_chatId; }
    Q_INVOKABLE bool                    isChat() const                         { return m_isChat; }
    Q_INVOKABLE QString                 chatName() const                       { return m_chatName; }
    Q_INVOKABLE VKContainerChatIcon*    chatIcon() const                       { return m_chatIcon; }


    void                                setUnreadCount(int arg)                { Q_ASSERT(arg >= 0);m_unreadCount = arg; }
    void                                setChatId(int arg)                     { m_chatId = arg; }
    void                                setIsChat(bool arg)                    { m_isChat = arg; }
    void                                setChatName(QString arg);
    void                                setChatIcon(VKContainerChatIcon* arg);
    void                                setMessage(VKContainerMessage* arg);

private:
    int                                 m_unreadCount;
    VKContainerMessage*                 m_message;
    int                                 m_chatId;
    bool                                m_isChat;
    QString                             m_chatName;
    VKContainerChatIcon*                m_chatIcon;
};


#endif // VKDIALOGHANDLER_H
