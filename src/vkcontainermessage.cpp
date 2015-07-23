#include "vkcontainermessage.h"
#include "vkhandlermessages.h"
#include "vkcontainermessageaction.h"

VKContainerMessage::VKContainerMessage(QObject *parent) :
    VKAbstractContainer(parent)
{
    m_user = NULL;
    m_attachments = NULL;
    setReadState(false);
}

VKContainerMessage::~VKContainerMessage()
{
}

VKContainerMessage *VKContainerMessage::fromJson(VKStorage *storage, QJsonObject obj, QJsonArray users, QVector<int> userIds) {
    VKContainerMessage* message = new VKContainerMessage;

    QDateTime date;
    date.setTime_t(obj.value("date").toInt());
    message->setMsgId(obj.value("id").toInt());
    message->setDate(date);
    message->setIsIncoming(obj.value("out").toInt() == 0);

    if (message->isIncoming()) {
        bool userFound = false;
        int id = obj.value("user_id").toInt();
        for (const auto &e : users) {
            auto el = e.toObject();
            if (el.value("id").toInt() == id) {
                auto user = VKContainerUser::fromJson(storage, el);
                message->setUser(user);
                userFound = true;
                break;
            }
        }
        if (!userFound) {
            message->setUser(new VKContainerUser);
            message->user()->valid(false);
            message->user()->setId(id);
            userIds.append(id);
        }
    } else {
        message->setUser(storage->getUserById(storage->ourUserId()));
    }

    message->setReadState(obj.value("read_state").toInt() == 1);

    message->setBody(obj.value("body").toString());
    if (obj.value("chat_id").isDouble()){
        message->setChatId(obj.value("chat_id").toInt());
    } else {
        message->setChatId(obj.value("user_id").toInt());
    }

    auto fwdMessages = obj.value("fwd_messages").toArray();
    for (auto e: fwdMessages) {
        auto fwd = e.toObject();
        QVector<int> unknownUsers;
        auto msg = VKContainerMessage::fromJson(storage, fwd, users, unknownUsers);
        message->addFwdMsg(msg);
        userIds += unknownUsers;
    }

    if (obj.contains("attachments")) {
        message->setAttachments( VKContainerAttachments::fromJson(storage, obj.value("attachments").toArray()) );
    }

    message->setAction(VKContainerMessageAction::fromJson(storage, obj, users, userIds));

    return message;
}

VKContainerMessage *VKContainerMessage::fromSql(VKStorage* storage, QSqlQuery &query) {
    VKContainerMessage* message = new VKContainerMessage;
    message->setMsgId(query.value("id").toInt());
    QDateTime date;
    date.setTime_t(query.value("date").toInt());
    message->setDate(date);
    message->setIsIncoming(query.value("incoming").toInt());
    message->setUser(storage->getUserById(query.value("user_id").toInt()));
    message->setReadState(query.value("read_state").toInt() == 1);
    message->setBody(query.value("body").toString());
    message->setIsChat(query.value("is_chat").toInt() == 1);
    message->setChatId(query.value("chat_id").toInt());

    return message;
}

void VKContainerMessage::complete(VKHandlerUsers *users) {
    for (int i=0;i<users->count();i++) {
        auto el = users->get(i);
        if (user()->id() == el->id()) {
            delete user();
            setUser(el);
        }
    }
    m_action->complete(users);
}


void VKContainerMessage::setUser(VKContainerUser *arg) {
    m_user = arg;
    m_user->setParent(this);
}

void VKContainerMessage::addFwdMsg(VKContainerMessage *arg) {
    m_fwd.append(arg);
    arg->setParent(this);
}

void VKContainerMessage::setAttachments(VKContainerAttachments *attachments) {
    m_attachments = attachments;
    attachments->setParent(this);
}

void VKContainerMessage::setAction(VKContainerMessageAction *action) {
    m_action = action;
    action->setParent(this);
}

bool VKContainerMessage::isValid() {
    return m_valid;
}

int VKContainerMessage::countFwd() {
    return m_fwd.count();
}

VKContainerMessage *VKContainerMessage::getFwd(int i) {
    return m_fwd.at(i);
}

