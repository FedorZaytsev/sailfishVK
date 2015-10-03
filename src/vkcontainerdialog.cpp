#include "vkcontainerdialog.h"
#include "vkcontainermessage.h"
#include "vkstorage.h"
#include "vkcontainerchaticon.h"

VKContainerDialog::VKContainerDialog(QObject *parent) :
    VKAbstractContainer(parent)
{
    m_unreadCount = 0;
    m_id = 0;
    m_isChat = false;
    m_type = eVKContainerDialog;
}

VKContainerDialog::~VKContainerDialog()
{
}

QSharedPointer<VKContainerDialog> VKContainerDialog::fromJson(VKStorage *storage, QJsonObject obj, const QJsonArray users, QVector<int> &userIds) {
    VKContainerDialog* dialog = new VKContainerDialog;
    dialog->setUnreadCount(obj.value("unread").toInt());

    QJsonObject message;
    if (obj.contains("message")) {
        message = obj.value("message").toObject();
    } else if (obj.contains("body") && obj.contains("id")) {
        message = obj;
        dialog->setUnreadCount(1);
    } else {
        qDebug()<<"unknown object for VKContainerDialog\nKeys:";
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


    auto chatIcon = QSharedPointer<VKContainerChatIcon>(new VKContainerChatIcon);
    if (message.value("photo_100").isString()) {
        chatIcon->add(message.value("photo_100").toString());
    } else {
        for (int i=0;i<4 && i<users.count();i++) {
            auto user = users.at(i).toObject();
            chatIcon->add(user.value("photo_100").toString());
        }
    }
    dialog->setChatIcon(chatIcon);


    auto containerMessage = VKContainerMessage::fromJson(storage, message, users, userIds);
    dialog->setMessage(containerMessage);
    return QSharedPointer<VKContainerDialog>(dialog);
}

void VKContainerDialog::complete(VKAbstractHandler *users) {
    m_message->complete(users);
    m_chatIcon->complete(users);
}

QDateTime VKContainerDialog::date() const {
    if (!m_message) {
        return QDateTime();
    }
    return m_message->date();
}

void VKContainerDialog::setUnreadCount(int arg) {
    Q_ASSERT(arg >= 0);

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
    SET_ARG_NOCHECK(m_chatIcon, arg);
    QObject::connect(m_chatIcon.data(), &VKAbstractContainer::dataChanged, [this](VKAbstractContainer* ) {
        emit this->dataChanged(this);
    });
}

void VKContainerDialog::setMessage(QSharedPointer<VKContainerMessage> arg) {
    SET_ARG_NOCHECK(m_message, arg);
    QObject::connect(m_message.data(), &VKAbstractContainer::dataChanged, [this](VKAbstractContainer* ) {
        emit this->dataChanged(this);
    });
}


