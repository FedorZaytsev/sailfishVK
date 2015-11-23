#include "vkvisualdialogmodel.h"

VKVisualDialogModel::VKVisualDialogModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

QHash<int, QByteArray> VKVisualDialogModel::roleNames() const {
    
    QHash<int, QByteArray> roles;
    roles[Roles::eRoleAuthorAvatar50] = "authorAvatar50";
    roles[Roles::eRoleIcon1] = "icon1";
    roles[Roles::eRoleIcon2] = "icon2";
    roles[Roles::eRoleIcon3] = "icon3";
    roles[Roles::eRoleIcon4] = "icon4";
    roles[Roles::eRoleId] = "id";
    roles[Roles::eRoleIsChat] = "isChat";
    roles[Roles::eRoleIsIncoming] = "isIncoming";
    roles[Roles::eRoleIsRead] = "isRead";
    roles[Roles::eRoleMsg] = "msg";
    roles[Roles::eRoleMsgId] = "msgId";
    roles[Roles::eRoleName] = "name";
    roles[Roles::eRoleOnline] = "online";
    roles[Roles::eRoleUnreadCount] = "unreadCount";
    roles[Roles::eRoleUserId] = "userId";
    
    return roles;
}

int VKVisualDialogModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_dialogs.count();
}

QVariant VKVisualDialogModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= m_dialogs.count()) {
        qDebug()<<"data for "<<index.row();
        Q_ASSERT(0);
        return QVariant();
    }

    auto dialog = m_dialogs[index.row()];

    switch (role) {
    case Roles::eRoleAuthorAvatar50:
        return dialog->firstMessage()->user()->iconSmall();
    case Roles::eRoleIcon1:
        return dialog->chatIcon()->get(0);
    case Roles::eRoleIcon2:
        return dialog->chatIcon()->get(1);
    case Roles::eRoleIcon3:
        return dialog->chatIcon()->get(2);
    case Roles::eRoleIcon4:
        return dialog->chatIcon()->get(3);
    case Roles::eRoleId:
        return dialog->id();
    case Roles::eRoleIsChat:
        return dialog->isChat();
    case Roles::eRoleIsIncoming:
        return dialog->firstMessage()->isIncoming();
    case Roles::eRoleIsRead:
        return dialog->firstMessage()->isRead();
    case Roles::eRoleMsg:
        return processMsg(dialog->firstMessage());
    case Roles::eRoleMsgId:
        return dialog->firstMessage()->id();
    case Roles::eRoleName:
        return dialog->chatName();
    case Roles::eRoleOnline:
        return dialog->firstMessage()->user()->isOnline();
    case Roles::eRoleUnreadCount:
        return dialog->firstMessage()->isIncoming() ? dialog->unreadCount() : 0;
    case Roles::eRoleUserId:
        return dialog->firstMessage()->user()->id();
    default:
        qDebug()<<"Error: Unknown role for dialog model"<<role;
        Q_ASSERT(0);
        break;
    }
    
    return QVariant();
}


void VKVisualDialogModel::addDialog(QSharedPointer<VKContainerDialog> dialog) {
    m_dialogs.append(dialog);
    QObject::connect(dialog.data(), &VKAbstractContainer::dataChanged, this, &VKVisualDialogModel::someDataChanged);
}

void VKVisualDialogModel::appendDialogs(VKStorage* storage, int count) {
    beginInsertRows(QModelIndex(), m_dialogs.count(), m_dialogs.count() + count - 1);

    int from = m_dialogs.count();
    int until = qMin(from + count, storage->sortedDialogsCount());
    for (int i=from;i<until;i++) {
        addDialog(storage->getDialogSortedByTime(i));
    }

    QObject::connect(storage, &VKStorage::dialogMoved, this, &VKVisualDialogModel::onDialogMove, Qt::UniqueConnection);
    QObject::connect(storage, &VKStorage::dialogRemoved, this, &VKVisualDialogModel::onDialogDelete, Qt::UniqueConnection);
    QObject::connect(storage, &VKStorage::dialogNew, this, &VKVisualDialogModel::onDialogCreated, Qt::UniqueConnection);

    endInsertRows();
}

int VKVisualDialogModel::count() {
    qDebug()<<m_dialogs.count();
    return m_dialogs.count();
}

QString VKVisualDialogModel::processMsg(QSharedPointer<VKContainerMessage> message) const {
    if (message->body().isEmpty()) {
        if (!message->attachments().isNull() && !message->attachments()->description().isEmpty()) {
            auto description = message->attachments()->description();
            description[0] = description[0].toUpper();
            return QString("[%1]").arg(description);
        }
        if (message->countFwd()) {
            return QString("[Forward message%1]").arg(message->countFwd()>1 ?"s":"");
        }
        if (!message->action()->text().isEmpty()) {
            return QString("[%1]").arg(message->action()->printable());
        }
    }

    return message->body();
}

void VKVisualDialogModel::someDataChanged(VKAbstractContainer *container) {
    auto dialog = reinterpret_cast<VKContainerDialog*>(container);

    qDebug()<<"dialog:"<<dialog->debugDescription();

    for (int i=0;i<m_dialogs.size();i++) {
        auto el = m_dialogs[i];
        if (el->id() == dialog->id()) {
            qDebug()<<"element at position"<<i<<"with id"<<dialog->id()<<dialog->firstMessage()->body().mid(0,10)<<"changed";
            emit dataChanged(index(i), index(i));
            return;
        }
    }

    qDebug()<<"Possible error: Cannot find container";
}

void VKVisualDialogModel::onDialogMove(int from, int to) {
    if (from != to) {
        qDebug()<<"from"<<from<<"to"<<to;
        if (to > from) {
            //fuck it
            //Qt documentation
            /*
             * However, when moving rows down in the same parent (sourceParent and destinationParent are equal),
             * the rows will be placed before the destinationChild index.
             * That is, if you wish to move rows 0 and 1 so they will become rows 1 and 2, destinationChild should be 3.
             */
            beginMoveRows(QModelIndex(), from, from, QModelIndex(), to+1);
        } else {
            beginMoveRows(QModelIndex(), from, from, QModelIndex(), to);
        }
        m_dialogs.move(from, to);
        endMoveRows();
    }
}

void VKVisualDialogModel::onDialogDelete(int idx) {
    qDebug()<<"idx"<<idx;
    beginRemoveRows(QModelIndex(), idx, idx);
    m_dialogs.removeAt(idx);
    endRemoveRows();

}

void VKVisualDialogModel::onDialogCreated(int position, QSharedPointer<VKContainerDialog> d) {
    qDebug()<<position;
    if (m_dialogs.count() < position) {
        return;
    }
    qDebug()<<"insert"<<m_dialogs.size();
    beginInsertRows(QModelIndex(), position, position);
    m_dialogs.insert(position, d);
    endInsertRows();
}


