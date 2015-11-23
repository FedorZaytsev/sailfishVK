#include "vkcontainermessageaction.h"
#include "vkhandlerusers.h"

VKContainerMessageAction::VKContainerMessageAction(VKStorage *storage, QObject *parent) :
    VKAbstractContainer(storage, parent)
{
    beginObjectChange();
    setType(ACTION_INVALID);
    setUserId(0);
    m_type = eVKContainerMessageAction;
    endObjectChange();
}

void VKContainerMessageAction::completed() {
    Q_ASSERT(!isValid());
    Q_ASSERT(storage()->isContainsUser(userId()));

    auto user = storage()->getUserById(userId());
    setText(user->firstName() + " " + user->lastName());
}

QString VKContainerMessageAction::printable() const {
    if (!isValid()) {
        return "";
    }

    switch(type()) {
    case ACTION_INVALID:
        return "";
    case ACTION_PHOTO_UPDATED:
        return tr("Chat photo updated");
    case ACTION_PHOTO_REMOVED:
        return tr("Chat photo removed");
    case ACTION_CHAT_CREATE:
        return QString(tr("Chat %1 created")).arg(text());
    case ACTION_TITLE_UPDATED:
        return QString(tr("Chat title updated to %1")).arg(text());
    case ACTION_INVITE_USER:
        return QString(tr("%1 invited")).arg(text());
    case ACTION_KICK_USER:
        return QString(tr("%1 kicked")).arg(text());
    }
    return "";
}

QSharedPointer<VKContainerMessageAction> VKContainerMessageAction::fromJson(VKStorage *storage, QJsonObject obj, QJsonArray users) {
    Q_UNUSED(storage);
    Q_UNUSED(users);

    auto action = QSharedPointer<VKContainerMessageAction>(new VKContainerMessageAction(storage));
    action->beginObjectChange();

    auto act = obj.value("action").toString();
    if (act == "") {
        action->setType( ACTION_INVALID );
        action->setInvalid();
    } else if (act == "chat_photo_update") {
        //todo
        action->setType( ACTION_PHOTO_UPDATED );
        action->setInvalid();
    } else if (act == "chat_photo_remove") {
        //todo
        action->setType( ACTION_PHOTO_REMOVED );
        action->setInvalid();
    } else if (act == "chat_create") {
        action->setType( ACTION_CHAT_CREATE );
        action->setText(obj.value("action_text").toString());
        action->setValid();
    } else if (act == "chat_title_update") {
        action->setType( ACTION_TITLE_UPDATED );
        action->setText(obj.value("action_text").toString());
        action->setValid();
    } else if (act == "chat_invite_user") {
        action->setType( ACTION_INVITE_USER );
        int userId = 0;
        if (obj.value("action_mid").isString()) {
            userId = obj.value("action_mid").toString().toInt();
        } else {
            userId = obj.value("action_mid").toInt();
        }
        if (userId < 0) {
            action->setText(obj.value("action_email").toString());
            action->setValid();
        } else {
            action->setUserId(userId);
            if (storage->isContainsUser(userId)) {
                auto user = storage->getUserById(userId);
                action->setText(user->firstName() + " " + user->lastName());
                action->setValid();
            } else {
                qDebug()<<"adding"<<userId;
                auto handler = new VKHandlerUsers(storage);
                handler->setUsers({userId});
                storage->helper()->request(action.data(), handler);
                action->setInvalid();
            }
        }
    } else if (act == "chat_kick_user") {
        action->setType( ACTION_KICK_USER );
        int userId = 0;
        if (obj.value("action_mid").isString()) {
            userId = obj.value("action_mid").toString().toInt();
        } else {
            userId = obj.value("action_mid").toInt();
        }
        if (userId < 0) {
            action->setText(obj.value("action_email").toString());
            action->setValid();
        } else {
            action->setUserId(userId);
            if (storage->isContainsUser(userId)) {
                auto user = storage->getUserById(userId);
                action->setText(user->firstName() + " " + user->lastName());
                action->setValid();
            } else {
                qDebug()<<"adding"<<userId;
                auto handler = new VKHandlerUsers(storage);
                handler->setUsers({userId});
                storage->helper()->request(action.data(), handler);
                action->setInvalid();
            }
        }
    } else {
        qDebug()<<"unknown action"<<act;
        Q_ASSERT(0);
    }

    action->endObjectChange();
    return action;
}


void VKContainerMessageAction::setType(int id) {
    SET_ARG(m_actionType, id);
}

void VKContainerMessageAction::setUserId(int id) {
    SET_ARG(m_actionMid, id);
}

void VKContainerMessageAction::setText(QString text) {
    SET_ARG(m_actionText, text);
}
