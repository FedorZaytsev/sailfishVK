#ifndef VKVISUALDIALOGMODEL_H
#define VKVISUALDIALOGMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <QModelIndex>
#include <QVector>
#include <QSharedPointer>
#include "vkcontainerdialog.h"
#include "vkcontainermessage.h"
#include "vkcontaineruser.h"
#include "vkcontainerchaticon.h"
#include "vkcontainermessageaction.h"

class VKVisualDialogModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit VKVisualDialogModel(QObject *parent = 0);

    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    
    void addDialog(QSharedPointer<VKContainerDialog> dialog);
    Q_INVOKABLE void appendDialogs(VKStorage *storage, int count);

    Q_INVOKABLE void test();
    
    enum Roles {
        eRoleName = Qt::UserRole + 1,
        eRoleMsg,
        eRoleIsIncoming,
        eRoleAuthorAvatar50,
        eRoleUserId,
        eRoleIsChat,
        eRoleOnline,
        eRoleId,
        eRoleMsgId,
        eRoleIcon1,
        eRoleIcon2,
        eRoleIcon3,
        eRoleIcon4,
        eRoleIsRead,
        eRoleUnreadCount
    };
private:
    QString processMsg(QSharedPointer<VKContainerMessage> message) const;
    
signals:

public slots:
    void someDataChanged(VKAbstractContainer* container);
private:

    QVector<QSharedPointer<VKContainerDialog>> m_dialogs;
};

#endif // VKVISUALDIALOGMODEL_H
