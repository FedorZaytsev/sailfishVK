#include "vkcontainermessageaction.h"
#include "vkhandlerusers.h"

VKContainerMessageAction::VKContainerMessageAction(QObject *parent) :
    VKAbstractContainer(parent)
{
    m_actionId = ACTION_INVALID;
    m_actionMid = 0;
}

VKContainerMessageAction *VKContainerMessageAction::fromJson(VKStorage *storage, QJsonObject obj, QJsonArray users, QVector<int> userIds) {
    Q_UNUSED(storage);
    Q_UNUSED(users);

    auto action = new VKContainerMessageAction;

    auto act = obj.value("action").toString();
    if (act == "") {
        action->setId( ACTION_INVALID );
    } else if (act == "chat_photo_update") {
        action->setId( ACTION_PHOTO_UPDATED );
    } else if (act == "chat_photo_remove") {
        action->setId( ACTION_PHOTO_REMOVED );
    } else if (act == "chat_create") {
        action->setId( ACTION_CHAT_CREATE );
        action->setText(obj.value("action_text").toString());
    } else if (act == "chat_title_update") {
        action->setId( ACTION_TITLE_UPDATED );
        action->setText(obj.value("action_text").toString());
    } else if (act == "chat_invite_user") {
        action->setId( ACTION_INVITE_USER );
        int userId = obj.value("action_mid").toInt();
        if (userId < 0) {
            action->setText(obj.value("action_email").toString());
        } else {
            userIds.append(userId);
            action->setUserId(userId);
        }
    } else if (act == "chat_kick_user") {
        action->setId( ACTION_KICK_USER );
        int userId = obj.value("action_mid").toInt();
        if (userId < 0) {
            action->setText(obj.value("action_email").toString());
        } else {
            userIds.append(userId);
            action->setUserId(userId);
        }
    } else {
        qDebug()<<"unknown action"<<act;
        Q_ASSERT(0);
    }

    return action;
}

void VKContainerMessageAction::complete(VKHandlerUsers *users) {
    for (int i=0;i<users->count();i++) {
        auto el = users->get(i);
        if (userId() == el->id()) {
            setText(el->firstName() + " " + el->lastName());
        }
    }
}
