#include "vkcontainerdialog.h"
#include "vkcontainermessage.h"
#include "vkstorage.h"
#include "vkcontainerchaticon.h"

VKContainerDialog::VKContainerDialog(VKStorage *storage, QObject *parent) :
    VKAbstractContainer(storage, parent)
{
    m_unreadCount = 0;
    m_id = 0;
    m_isChat = false;
    m_type = eVKContainerDialog;
    m_typingUsers = new VKUserTyping(this);
}

VKContainerDialog::~VKContainerDialog()
{
}

QSharedPointer<VKContainerDialog> VKContainerDialog::fromJson(VKStorage *storage, QJsonObject obj, const QJsonArray users) {
    auto dialog = QSharedPointer<VKContainerDialog>(new VKContainerDialog(storage));
    dialog->beginObjectChange();

    dialog->setUnreadCount(obj.value("unread").toInt());

    QJsonObject message;
    if (obj.contains("message")) {
        message = obj.value("message").toObject();
    } else if (obj.contains("body") && obj.contains("id")) {
        message = obj;
        dialog->setUnreadCount(1);
    } else {
        qDebug()<<"Unknown object for VKContainerDialog";
        qDebug()<<"Keys:";
        for (auto it = message.begin();it != message.end(); ++it) {
            qDebug()<<it.key();
        }
        Q_ASSERT(0);
    }

    if (message.contains("chat_id")) {
        dialog->setIsChat(true);
        dialog->setId(message.value("chat_id").toInt());
    } else {
        dialog->setIsChat(false);
        dialog->setId(message.value("user_id").toInt());
    }

    if (message.value("title").toString() != " ... ") {
        dialog->setChatName(message.value("title").toString());
    } else {
        int user_id = message.value("user_id").toInt();
        bool b = false;
        for (auto e : users) {
            auto el = e.toObject();
            if (el.value("id").toInt() == user_id) {
                dialog->setChatName(QString("%1 %2") .arg(el.value("first_name").toString()) .arg(el.value("last_name").toString()));
                b = true;
                break;
            }
        }
        if (!b) {
            dialog->setChatName(message.value("title").toString());
        }
    }


    auto chatIcon = QSharedPointer<VKContainerChatIcon>(new VKContainerChatIcon(storage));
    if (message.value("photo_100").isString()) {
        chatIcon->add(message.value("photo_100").toString());
    } else {
        for (int i=0;i<4 && i<users.count();i++) {
            auto user = users.at(i).toObject();
            chatIcon->add(user.value("photo_100").toString());
        }
    }
    dialog->setChatIcon(chatIcon);


    auto containerMessage = VKContainerMessage::fromJson(storage, message, users);
    storage->addMessage(containerMessage);

    dialog->endObjectChange();
    dialog->setValid();
    return dialog;
}


QDateTime VKContainerDialog::date() const {
    auto message = firstMessage();

    if (message.isNull()) {
        return QDateTime();
    } else {
        return message->date();
    }
}

QSharedPointer<VKContainerMessage> VKContainerDialog::firstMessage() const {
    return getMessageByIndex(0);
}

QSharedPointer<VKContainerMessage> VKContainerDialog::getMessageByIndex(int idx) const {
    if (idx >= m_messagesSorted.size()) {
        return QSharedPointer<VKContainerMessage>(new VKContainerMessage(storage()));
    }

    return m_messagesSorted[idx];
}

QSharedPointer<VKContainerMessage> VKContainerDialog::getMessageById(int id) const {
    if (m_messages.contains(id)) {
        return m_messages[id];
    }

    return QSharedPointer<VKContainerMessage>();
}

void VKContainerDialog::removeMessage(int idx) {
    Q_ASSERT(idx < m_messages.size());

    m_messages.remove(idx);
    removeSorted(idx);
}

int VKContainerDialog::appendMessage(QSharedPointer<VKContainerMessage> msg) {
    int pos = -1;
    if (!msg->isDeleted()) {
        pos = insertSorted(msg);
    }

    if (!m_messages.contains(msg->id())) {
        QObject::connect(msg.data(), &VKContainerMessage::deleted, this, &VKContainerDialog::onMessageDeleted);
        m_messages[msg->id()] = msg;
    }
    return pos;
}

QSharedPointer<VKContainerMessage> VKContainerDialog::findMessage(int id) const {
    if (m_messages.contains(id)) {
        return m_messages[id];
    }
    Q_ASSERT(0);
    return QSharedPointer<VKContainerMessage>();
}

QSharedPointer<VKContainerChatIcon> VKContainerDialog::chatIcon() const {
    if (m_chatIcon.isNull()) {
        return QSharedPointer<VKContainerChatIcon>(new VKContainerChatIcon(storage()));
    }

    return m_chatIcon;
}

bool VKContainerDialog::isDeleted() const {
    return m_messagesSorted.size() == 0;
}

void VKContainerDialog::setUnreadCount(int arg) {
    //Q_ASSERT(arg >= 0);

    SET_ARG(m_unreadCount, arg);
}

void VKContainerDialog::setId(int arg) {
    SET_ARG(m_id, arg);
}

void VKContainerDialog::setIsChat(bool arg) {
    SET_ARG(m_isChat, arg);
}

void VKContainerDialog::setChatName(QString arg) {
    SET_ARG(m_chatName, arg);
}

void VKContainerDialog::setChatIcon(QSharedPointer<VKContainerChatIcon> arg) {
    if (!m_chatIcon.isNull()) {
        QObject::disconnect(m_chatIcon.data(),SLOT(dataChanged(VKAbstractContainer*)));
    }

    SET_ARG_NOCHECK(m_chatIcon, arg);
    QObject::connect(m_chatIcon.data(), &VKAbstractContainer::dataChanged, [this](VKAbstractContainer* ) {
        emit this->dataChanged(this);
    });
}

void VKContainerDialog::addUserTyping(QSharedPointer<VKContainerUser> user, u_int32_t time) {
    m_typingUsers->add(user, time);
}

QString VKContainerDialog::debugDescription() {
    if (m_messagesSorted.size()) {
        return QString("name:%1 id:%2 unread:%3 message:%4").arg(m_chatName).arg(m_id).arg(m_unreadCount).arg(m_messagesSorted[0]->debugDescription());
    } else {
        return QString("name:%1 id:%2 unread:%3").arg(m_chatName).arg(m_id).arg(m_unreadCount);
    }
}

bool VKContainerDialog::updateFrom(QSharedPointer<VKContainerDialog> dialog) {
    qDebug()<<"updating dialog"<<dialog->debugDescription();
    bool updated = false;
    UPDATE_ARG_CHECK(dialog,        unreadCount,    setUnreadCount, updated);
    UPDATE_ARG_CHECK(dialog,        isChat,         setIsChat,      updated);
    UPDATE_ARG_CHECK(dialog,        chatName,       setChatName,    updated);
    UPDATE_ARG_CHECK_SHARED(dialog, chatIcon,       setChatIcon,    updated);

    return updated;
}

void VKContainerDialog::completed() {
    Q_ASSERT(0);
}

int VKContainerDialog::insertSorted(QSharedPointer<VKContainerMessage> message) {
    Q_ASSERT(!message->isDeleted());

    auto it = std::lower_bound(m_messagesSorted.begin(), m_messagesSorted.end(), message, VKStorageComparator());
    int position = it - m_messagesSorted.begin();

    if (position == m_messagesSorted.size() || (m_messagesSorted[position]->id() != message->id())) {
        qDebug()<<"inserting element at position"<<position;
        if (position == 0) {
            if (m_messagesSorted.size()) {
                auto first = m_messagesSorted[position];
                QObject::disconnect(first.data(), &VKContainerMessage::dataChanged, this, &VKContainerDialog::onMessageChanged);
            }
            QObject::connect(message.data(), &VKContainerMessage::dataChanged, this, &VKContainerDialog::onMessageChanged);
        }

        m_messagesSorted.insert(position, message);

        if (position == 0) {
            storage()->onFirstMessageInDialogChanged(storage()->getDialogById(id()));
            emitChange();
        }
    }
    return position;
}

void VKContainerDialog::removeSorted(int id) {
    qDebug()<<"id"<<id;
    int idx = -1;
    for (int i=0;i<m_messagesSorted.size();i++) {
        if (m_messagesSorted[i]->id() == id) {
            idx = i;
            break;
        }
    }
    Q_ASSERT(idx != -1);
    auto message = m_messagesSorted[idx];

    if (idx == 0) {
        QObject::disconnect(message.data(), &VKContainerMessage::dataChanged, this, &VKContainerDialog::onMessageChanged);
        if (m_messagesSorted.size() > 1) {
            qDebug()<<"setting connection";
            QObject::connect(m_messagesSorted[idx+1].data(), &VKContainerMessage::dataChanged, this, &VKContainerDialog::onMessageChanged);
        }
    }
    qDebug()<<"removing"<<idx;

    m_messagesSorted.remove(idx);

    if (idx == 0) {
        storage()->onFirstMessageInDialogChanged(storage()->getDialogById(this->id()));
        emitChange();
    }
}

void VKContainerDialog::onMessageChanged(VKAbstractContainer *c) {

    VKContainerMessage* _msg = dynamic_cast<VKContainerMessage*>(c);
    auto message = storage()->getMessageById(_msg->id());

    auto needUpdate = firstMessage()->id() == message->id();

    if (needUpdate) {
        emitChange();
    }

}

void VKContainerDialog::onMessageDeleted(VKContainerMessage *_msg) {
    auto message = storage()->getMessageById(_msg->id());
    qDebug()<<message->id()<<message->isDeleted()<<message->body().mid(0,20);

    if (message->isDeleted()) {
        if (!message->isRead() && message->isIncoming()) {
            setUnreadCount(unreadCount() - 1);
        }

        removeSorted(message->id());
    } else {
        if (!message->isRead() && message->isIncoming()) {
            setUnreadCount(unreadCount() + 1);
        }

        insertSorted(message);
    }

}


