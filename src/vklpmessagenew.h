#ifndef VKLPMESSAGENEW_H
#define VKLPMESSAGENEW_H

#include "vklpabstract.h"
#include "vklpeventtype.h"
#include "vklongpollupdateparser.h"
#include "vkcontainerdialog.h"
#include "vkcontainermessage.h"

#define MAX_USER_ID 2000000000

class VKLPMessageNew : public VKLPAbstract
{
    Q_OBJECT
public:
    explicit VKLPMessageNew(QObject *parent = 0);
    void fromLP(const QJsonArray &data, QList<QString> &msgs, QList<QString> &users, QList<QString> &chats);
    virtual void complete(QVector<QSharedPointer<VKContainerDialog>> dialogs, QVector<QSharedPointer<VKContainerMessage>> messages, QVector<QSharedPointer<VKContainerUser>> users);

    Q_INVOKABLE int id() { return m_id; }
    Q_INVOKABLE bool isChat() { return m_isChat; }
    Q_INVOKABLE int userId() { return m_userId; }
    Q_INVOKABLE VKContainerDialog* dialogPtr() { return m_dialog.data(); }

    QSharedPointer<VKContainerDialog> dialog() { return m_dialog; }
signals:

public slots:
private:
    int m_id;
    bool m_isChat;
    int m_userId;
    QSharedPointer<VKContainerDialog> m_dialog;
};

#endif // VKLPMESSAGENEW_H
