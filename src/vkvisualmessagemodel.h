#ifndef VKVISUALMESSAGEMODEL_H
#define VKVISUALMESSAGEMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <QModelIndex>
#include <QVector>
#include <QSharedPointer>
#include "vkcontainerdialog.h"
#include "vkcontainermessage.h"
#include "vkcontaineruser.h"
#include "vkcontainermessageaction.h"
#include "vkvisibleparseattachments.h"


class VKVisualMessageModelData {
public:
    VKVisualMessageModelData(){}
    VKVisualMessageModelData(QSharedPointer<VKContainerMessage> m) {
        m_message = m;
        m_isMain = false;
    }
    VKVisualMessageModelData(const VKVisualMessageModelData &data) {
        this->m_message = data.message();
        this->m_additional = data.additional();
        this->m_isMain = data.isMain();
    }


    QSharedPointer<VKContainerMessage> message() const { return m_message; }
    QMap<int, QVariant> additional() const { return m_additional; }
    QVariant data(int idx) const { return m_additional[idx]; }
    bool contain(int idx) const { return m_additional.contains(idx); }
    void add(int idx, QVariant var) { m_additional[idx] = var; }
    void setIsMain(bool b) { m_isMain = b; }
    bool isMain() const { return m_isMain; }

private:
    QSharedPointer<VKContainerMessage> m_message;
    QMap<int, QVariant> m_additional;
    bool m_isMain;
};

class VKVisualMessageModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit VKVisualMessageModel(QObject *parent = 0);

    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE void setProperty(int index, int role, const QVariant & value);

    void addMessage(QSharedPointer<VKContainerMessage> message, int position = 0);
    Q_INVOKABLE void appendMessages(VKStorage *storage, int chatId, int count);

    Q_INVOKABLE QVariant get(int idx, int role);


    enum Roles {
        eRoleId = Qt::UserRole + 1,
        eRoleMsg,
        eRoleDate,
        eRoleUserName,
        eRoleIcon,
        eRoleIncoming,
        eRoleOffset,
        eRoleHighlight,
        eRoleIsRead,
        eRoleAttachments,
        eRoleChatId,
        eRoleGuid,
        eRoleActionMessages,
    };

    Q_ENUMS(Roles)
private:
    void addMessage(QSharedPointer<VKContainerMessage> message, int position, int offset);
    QString processAction(QSharedPointer<VKContainerMessage> message) const;
    QVariantMap processAttachments(QSharedPointer<VKContainerMessage> message) const;
    QString processDate(QDateTime time) const;
    int addMessageAtCalculatedPosition(QSharedPointer<VKContainerMessage> message, int position, int offset);

signals:

public slots:
    void someDataChanged(VKAbstractContainer* container);
    void onMessageCreated(int position, QSharedPointer<VKContainerMessage> message);
    void onMessageRemoved(int chatId, int position);
private:

    QVector<VKVisualMessageModelData> m_messages;
};

#endif // VKVISUALMESSAGEMODEL_H
