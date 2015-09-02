#ifndef VKCONTAINERMESSAGEACTION_H
#define VKCONTAINERMESSAGEACTION_H

#include "vkabstractcontainer.h"
#include "vkstorage.h"

class VKHandlerUsers;
class VKContainerMessageAction : public VKAbstractContainer
{
    Q_OBJECT
public:
    explicit VKContainerMessageAction(QObject *parent = 0);

    static QSharedPointer<VKContainerMessageAction> fromJson(VKStorage* storage, QJsonObject obj, const QJsonArray users, QVector<int> &userIds);
    virtual void complete(VKAbstractHandler* _h);

    enum Enum {
        ACTION_INVALID,
        ACTION_PHOTO_UPDATED,
        ACTION_PHOTO_REMOVED,
        ACTION_CHAT_CREATE,
        ACTION_TITLE_UPDATED,
        ACTION_INVITE_USER,
        ACTION_KICK_USER
    };

    Q_ENUMS(Enum)

    Q_INVOKABLE int type() { return m_actionType; }
    Q_INVOKABLE int userId() { return m_actionMid; }
    Q_INVOKABLE QString text() { return m_actionText; }

    void setType(int id) { m_actionType = id; }
    void setUserId(int id) { m_actionMid = id; }
    void setText(QString text) { m_actionText = text; }

signals:

public slots:
private:
    int                             m_actionType;
    int                             m_actionMid;
    QString                         m_actionText;
};

#endif // VKCONTAINERMESSAGEACTION_H
