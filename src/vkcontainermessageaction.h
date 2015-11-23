#ifndef VKCONTAINERMESSAGEACTION_H
#define VKCONTAINERMESSAGEACTION_H

#include "vkabstractcontainer.h"
#include "vkstorage.h"

class VKHandlerUsers;
class VKContainerMessageAction : public VKAbstractContainer
{
    Q_OBJECT
public:
    explicit VKContainerMessageAction(VKStorage *storage, QObject *parent = 0);

    static QSharedPointer<VKContainerMessageAction> fromJson(VKStorage* storage, QJsonObject obj, const QJsonArray users);
    virtual void completed();

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

    Q_INVOKABLE int type() const { return m_actionType; }
    Q_INVOKABLE int userId() const { return m_actionMid; }
    Q_INVOKABLE QString text() const { return m_actionText; }
    Q_INVOKABLE QString printable() const;

    void setType(int id);
    void setUserId(int id);
    void setText(QString text);

signals:

public slots:
private:
    int                             m_actionType;
    int                             m_actionMid;
    QString                         m_actionText;
};

#endif // VKCONTAINERMESSAGEACTION_H
