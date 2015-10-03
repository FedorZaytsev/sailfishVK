#include "vkcontainermessage.h"
#include "vkhandlermessages.h"
#include "vkcontainermessageaction.h"
#include "vkemojiparser.h"

VKContainerMessage::VKContainerMessage(QObject *parent) :
    VKAbstractContainer(parent)
{
    setReadState(false);
    m_type = eVKContainerMessage;
}

VKContainerMessage::~VKContainerMessage()
{
}

QSharedPointer<VKContainerMessage> VKContainerMessage::fromJson(VKStorage *storage, QJsonObject obj, QJsonArray users, QVector<int> &userIds) {
    auto message = QSharedPointer<VKContainerMessage>(new VKContainerMessage);

    QDateTime date;
    date.setTime_t(obj.value("date").toInt());
    message->setId(obj.value("id").toInt());
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
            message->setUser(QSharedPointer<VKContainerUser>(new VKContainerUser));
            message->user()->valid(false);
            message->user()->setId(id);
            userIds.append(id);
        }
    } else {
        message->setUser(storage->getUserById(storage->ourUserId()));
    }

    message->setReadState(obj.value("read_state").toInt() == 1);

    auto body = obj.value("body").toString();
    if (obj.contains("emoji") && obj.value("emoji").toInt() == 1) {
        VKContainerMessage::processEmoji(body);
    }
    message->setBody(body);

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

    message->setAttachments( VKContainerAttachments::fromJson(storage, obj.value("attachments").toArray()));

    message->setAction(VKContainerMessageAction::fromJson(storage, obj, users, userIds));

    return message;
}

void VKContainerMessage::complete(VKAbstractHandler *_h) {
    auto h = dynamic_cast<VKHandlerUsers*>(_h);
    for (int i=0;i<h->count() && h;i++) {
        auto el = h->get(i);
        if (user()->id() == el->id()) {
            qDebug()<<"Message with id"<<id()<<"completed with user id"<<el->id();
            setUser(el);
            break;
        }
    }
    for (auto e: m_fwd) {
        e->complete(_h);
    }
    m_action->complete(h);
    m_user->complete(h);
    m_attachments->complete(h);
}


void VKContainerMessage::setUser(QSharedPointer<VKContainerUser> arg) {
    SET_ARG_NOCHECK(m_user, arg);
    QObject::connect(m_user.data(), &VKAbstractContainer::dataChanged, [this](VKAbstractContainer* ) {
        emit this->dataChanged(this);
    });
}

void VKContainerMessage::addFwdMsg(QSharedPointer<VKContainerMessage> arg) {
    arg->setReadState(readState());
    m_fwd.append(arg);
    emit dataChanged(this);
    QObject::connect(arg.data(), &VKAbstractContainer::dataChanged, [this](VKAbstractContainer* ) {
        emit this->dataChanged(this);
    });
}

void VKContainerMessage::setAttachments(QSharedPointer<VKContainerAttachments> attachments) {
    SET_ARG_NOCHECK(m_attachments, attachments);
    QObject::connect(m_attachments.data(), &VKAbstractContainer::dataChanged, [this](VKAbstractContainer* ) {
        emit this->dataChanged(this);
    });
}

void VKContainerMessage::setAction(QSharedPointer<VKContainerMessageAction> action) {
    SET_ARG_NOCHECK(m_action, action);
    QObject::connect(m_action.data(), &VKAbstractContainer::dataChanged, [this](VKAbstractContainer* ) {
        emit this->dataChanged(this);
    });
}

void VKContainerMessage::setReadState(bool arg) {
    SET_ARG_NOCHECK(m_readState, arg);
    for (auto e: m_fwd) {
        e->setReadState(arg);
    }
}

void VKContainerMessage::processEmoji(QString &s) {

    VKEmojiParser parser;
    parser.parse(s);
}


bool VKContainerMessage::isValid() {
    return m_valid;
}

int VKContainerMessage::countFwd() {
    return m_fwd.count();
}

VKContainerMessage* VKContainerMessage::getFwdPtr(int i) const {
    return m_fwd.at(i).data();
}

QSharedPointer<VKContainerMessage> VKContainerMessage::getFwd(int i) const {
    return m_fwd.at(i);
}

void VKContainerMessage::setId(int arg) {
    SET_ARG(m_id, arg);
}

void VKContainerMessage::setDate(QDateTime arg) {
    SET_ARG(m_date, arg);
}

void VKContainerMessage::setIsIncoming(bool arg) {
    SET_ARG(m_isIncoming, arg);
}

void VKContainerMessage::setBody(QString arg) {
    SET_ARG(m_body, arg);
}

void VKContainerMessage::setIsChat(bool arg) {
    SET_ARG(m_isChat, arg);
}

void VKContainerMessage::setChatId(int arg) {
    SET_ARG(m_chatId, arg);
}

