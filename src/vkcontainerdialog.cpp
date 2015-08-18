#include "vkcontainerdialog.h"
#include "vkcontainermessage.h"
#include "vkstorage.h"
#include "vkcontainerchaticon.h"

VKContainerDialog::VKContainerDialog(QObject *parent) :
    VKAbstractContainer(parent)
{
    m_message = NULL;
    m_chatIcon = NULL;
    m_unreadCount = 0;
    m_chatId = 0;
    m_isChat = false;
}

VKContainerDialog::~VKContainerDialog()
{
}

VKContainerDialog* VKContainerDialog::fromJson(VKStorage *storage, QJsonObject obj, const QJsonArray users, QVector<int> userIds) {
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
        dialog->setChatId(message.value("chat_id").toInt());
    } else {
        dialog->setIsChat(false);
        dialog->setChatId(message.value("user_id").toInt());
    }

    if (message.value("title").toString() != " ... ") {
        dialog->setChatName(message.value("title").toString());
    } else {
        int user_id = message.value("user_id").toInt();
        for (auto e : users) {
            auto el = e.toObject();
            if (el.value("id").toInt() == user_id) {
                dialog->setChatName(QString("%1 %2") .arg(el.value("first_name").toString()) .arg(el.value("last_name").toString()));
                break;
            }
        }
    }


    VKContainerChatIcon* chatIcon = new VKContainerChatIcon;
    if (message.value("photo_100").isString()) {
        chatIcon->add(message.value("photo_100").toString());
    } else {
        for (int i=0;i<4 && i<users.count();i++) {
            auto user = users.at(i).toObject();
            chatIcon->add(user.value("photo_100").toString());
        }
    }
    dialog->setChatIcon(chatIcon);


    VKContainerMessage* containerMessage = VKContainerMessage::fromJson(storage, message, users, userIds);
    containerMessage->setParent(dialog);
    dialog->setMessage(containerMessage);
    return dialog;
}

VKContainerDialog *VKContainerDialog::fromSql(VKStorage *storage, QSqlQuery query) {
    VKContainerDialog* dialog = new VKContainerDialog;
    dialog->setChatId(query.value("id").toInt());
    dialog->setMessage(storage->getMessageById(query.value("last_message_id").toInt()));
    dialog->setUnreadCount(query.value("unread_count").toInt());
    dialog->setIsChat(query.value("is_chat").toInt() == 1);
    dialog->setChatName(query.value("name").toString());

    for (int i=0;i<4;i++) {
        QString iconName = query.value(QString("icon%1").arg(i)).toString();
        if (iconName == "") break;

    }

    return dialog;
}

void VKContainerDialog::setChatName(QString arg) {
    m_chatName = arg;
}

void VKContainerDialog::setChatIcon(VKContainerChatIcon *arg) {
    m_chatIcon = arg;
    m_chatIcon->setParent(this);
}

void VKContainerDialog::setMessage(VKContainerMessage *arg) {
    m_message = arg;
    m_message->setParent(this);
}


