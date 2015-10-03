#include "vkvisualdialogmodel.h"

VKVisualDialogModel::VKVisualDialogModel(QObject *parent) :
    QAbstractListModel(parent)
{
    qDebug()<<"created";
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
        return dialog->message()->user()->iconSmall();
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
        return dialog->message()->isIncoming();
    case Roles::eRoleIsRead:
        return dialog->message()->readState();
    case Roles::eRoleMsg:
        return processMsg(dialog->message());
    case Roles::eRoleMsgId:
        return dialog->message()->id();
    case Roles::eRoleName:
        return dialog->chatName();
    case Roles::eRoleOnline:
        return dialog->message()->user()->isOnline();
    case Roles::eRoleUnreadCount:
        return dialog->message()->isIncoming() ? dialog->unreadCount() : 0;
    case Roles::eRoleUserId:
        return dialog->message()->user()->id();
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
    for (int i=0;i<count;i++) {
        addDialog(storage->getDialogSortedByTime(from + i));
    }

    endInsertRows();
}

void VKVisualDialogModel::test() {
    qDebug()<<"test"<<m_dialogs[1]->chatName();
    m_dialogs[1]->message()->setBody("ahahaha body");
}

QString VKVisualDialogModel::processMsg(QSharedPointer<VKContainerMessage> message) const {
    if (message->body().isEmpty()) {
        if (!message->attachments().isNull() && !message->attachments()->description().isEmpty()) {
            auto description = message->attachments()->description();
            description[0] = description[0].toUpper();
            return description;
        }
        if (message->countFwd()) {
            return QString("[Forward message%1]").arg(message->countFwd()>1 ?"s":"");
        }
        if (!message->action()->text().isEmpty()) {
            return QString("[%s]").arg(message->action()->text());
        }
    }

    return message->body();
}

void VKVisualDialogModel::someDataChanged(VKAbstractContainer *container) {
    auto dialog = reinterpret_cast<VKContainerDialog*>(container);

    qDebug()<<"dialog:"<<dialog->id()<<dialog->chatName();
    qDebug()<<"dialog[1]"<<m_dialogs[1]->chatName();

    for (int i=0;i<m_dialogs.size();i++) {
        auto el = m_dialogs[i];
        if (el->id() == dialog->id()) {
            qDebug()<<"element at position"<<i<<"with id"<<dialog->id()<<"changed";
            emit dataChanged(index(i), index(i));
            return;
        }
    }

    qDebug()<<"Cannot find container";
    Q_ASSERT(0);

}


