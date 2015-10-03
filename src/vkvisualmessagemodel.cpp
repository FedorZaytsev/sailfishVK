#include "vkvisualmessagemodel.h"

VKVisualMessageModel::VKVisualMessageModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

QHash<int, QByteArray> VKVisualMessageModel::roleNames() const {

    QHash<int, QByteArray> roles;

    roles[eRoleActionMessages] = "actionMessages";
    roles[eRoleAttachments] = "attachments";
    roles[eRoleChatId] = "chatId";
    roles[eRoleDate] = "date";
    roles[eRoleGuid] = "guid";
    roles[eRoleHighlight] = "highlight";
    roles[eRoleIcon] = "icon";
    roles[eRoleId] = "id";
    roles[eRoleIncoming] = "incoming";
    roles[eRoleIsRead] = "isRead";
    roles[eRoleMsg] = "msg";
    roles[eRoleOffset] = "offset";
    roles[eRoleUserName] = "userName";

    return roles;
}

int VKVisualMessageModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_messages.count();
}

QVariant VKVisualMessageModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= rowCount()) {
        qDebug()<<"index is out of range"<<index.row()<<"row count"<<rowCount();
    }

    auto& obj = m_messages[index.row()];

    switch (role) {
    case eRoleActionMessages:
        return processAction(obj.message());
    case eRoleChatId:
        return obj.message()->chatId();
    case eRoleDate:
        return processDate(obj.message()->date());
    case eRoleIcon:
        return obj.message()->user()->iconSmall();
    case eRoleId:
        return obj.message()->id();
    case eRoleIncoming:
        return obj.message()->isIncoming();
    case eRoleIsRead:
        return obj.message()->readState();
    case eRoleMsg:
        return obj.message()->body();
    case eRoleUserName:
        return obj.message()->user()->userName();
    default: {
        if (obj.contain(role)) {
            return obj.data(role);
        }
    }
    }
    return QVariant();
}

void VKVisualMessageModel::setProperty(int idx, int role, const QVariant &value) {
    if (idx < 0 || idx >= m_messages.count()) {
        qDebug()<<"invalid index"<<idx;
        Q_ASSERT(0);
        return;
    }

    //If not user defined role, do not process
    if (role < Qt::UserRole) return;

    if (!m_messages[idx].contain(role)) {
        qDebug()<<"invalid role"<<role<<"for index"<<idx;
        Q_ASSERT(0);
        return;
    }

    m_messages[idx].add(role, value);

    emit dataChanged(index(idx), index(idx), {role});
}


void VKVisualMessageModel::addMessage(QSharedPointer<VKContainerMessage> message) {
    addMessage(message, 0);
}

void VKVisualMessageModel::appendMessages(VKStorage *storage, int count) {
    qDebug()<<"append"<<m_messages.count()<<(m_messages.count() + count - 1);
    beginInsertRows(QModelIndex(), m_messages.count(), m_messages.count() + count - 1);

    int from = m_messages.count();
    for (int i=0;i<count;i++) {
        addMessage(storage->getMessageSortedByTime(from + i));
    }

    endInsertRows();
}

QVariant VKVisualMessageModel::get(int idx, int role) {
    return data(index(idx), role);
}

void VKVisualMessageModel::addMessage(QSharedPointer<VKContainerMessage> message, int offset) {
    for (int i=message->countFwd()-1;i>=0;i--) {
        addMessage(message->getFwd(i), offset + 1);
    }

    VKVisualMessageModelData data(message);

    data.add(eRoleGuid, 0);
    data.add(eRoleHighlight, false);
    data.add(eRoleOffset, offset);
    data.add(eRoleAttachments, processAttachments(message));

    QObject::connect(message.data(), &VKAbstractContainer::dataChanged, this, &VKVisualMessageModel::someDataChanged);

    m_messages.append(data);
}

QString VKVisualMessageModel::processAction(QSharedPointer<VKContainerMessage> message) const {

    auto action = message->action();
    auto userName = message->user()->userName();

    switch (action->type()) {
    case VKContainerMessageAction::ACTION_CHAT_CREATE:
        return QString("Chat created by %1").arg(userName);
    case VKContainerMessageAction::ACTION_INVITE_USER:
        return QString("%1 invited %2").arg(userName).arg(action->text());
    case VKContainerMessageAction::ACTION_KICK_USER:
        return QString("%1 kicked %2").arg(userName).arg(action->text());
    case VKContainerMessageAction::ACTION_PHOTO_REMOVED:
        return QString("Photo removed by %1").arg(userName);
    case VKContainerMessageAction::ACTION_PHOTO_UPDATED:
        return QString("Photo updated by %1").arg(userName);
    case VKContainerMessageAction::ACTION_TITLE_UPDATED:
        return QString("%1 updated title to %2").arg(action->text());
    default:
        return "";
    }
}

QVariantMap VKVisualMessageModel::processAttachments(QSharedPointer<VKContainerMessage> message) const {

    QVariantMap m;
    VKVisibleParseAttachments parser;
    parser.parse(message->attachments(), m);

    return m;
}

QString VKVisualMessageModel::processDate(QDateTime time) const {
    qint64 secs = time.secsTo(QDateTime::currentDateTime());
    if (secs/60/60/24 > 0) {
        return time.toString("h:mm, dd.MMM");
    } else {
        return time.toString("h:mm:ss");
    }
}

void VKVisualMessageModel::someDataChanged(VKAbstractContainer *container) {
    auto message = reinterpret_cast<VKContainerMessage*>(container);

    for (int i=0;i<m_messages.size();i++) {
        auto el = m_messages[i];
        if (el.message()->id() == message->id()) {
            qDebug()<<"element at position"<<i<<"with id"<<message->id()<<"changed";
            emit dataChanged(index(i), index(i));
            return;
        }
    }

    qDebug()<<"Cannot find container";
    Q_ASSERT(0);
}



