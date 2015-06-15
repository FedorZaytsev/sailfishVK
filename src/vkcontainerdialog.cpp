#include "vkcontainerdialog.h"
#include "vkcontainermessage.h"
#include "vkstorage.h"
#include "vkcontainerchaticon.h"

VKContainerDialog::VKContainerDialog(QObject *parent) :
    VKAbstractContainer(parent)
{
    m_message = NULL;
    m_chatIcon = NULL;
    //qDebug()<<"VKContainerDialog::VKContainerDialog create";
}


VKContainerDialog::~VKContainerDialog()
{
    if (m_message) {
        delete m_message;
    }
    if (m_chatIcon) {
        delete m_chatIcon;
    }
    //qDebug()<<"VKContainerDialog::~VKContainerDialog";
}

VKContainerDialog* VKContainerDialog::fromJson(VKStorage *storage, QJsonObject obj, const QJsonArray users) {
    VKContainerDialog* dialog = new VKContainerDialog;
    dialog->setUnreadCount(obj.value("unread").toInt(0));
    QJsonObject message = obj.value("message").toObject();
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
                dialog->setChatName(QString("%1 %2") .arg(el.value("first_name").toString()) .arg(el.value("las_name").toString()));
                break;
            }
        }
    }

    //must be list, because if there is no icon in chat, 4 avators are requested

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


    VKContainerMessage* containerMessage = VKContainerMessage::fromJson(storage, obj.value("message").toObject(), users);
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

void VKContainerDialog::setMessage(VKContainerMessage *arg) {
    m_message = arg; m_message->setParent(this);
}


