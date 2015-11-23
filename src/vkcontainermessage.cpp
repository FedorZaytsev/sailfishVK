#include "vkcontainermessage.h"
#include "vkhandlermessages.h"
#include "vkcontainermessageaction.h"
#include "vkcontainerdialog.h"
#include "vkemojiparser.h"
#include "vkcontainerdialog.h"
#include "vkhandlerusers.h"
#include "vkhandlerdialogbyid.h"
#include "vkcontainerchaticon.h"


VKContainerMessage::VKContainerMessage(VKStorage *storage, QObject *parent) :
    VKAbstractContainer(storage, parent)
{
    beginObjectChange();
    m_readState = UNKNOWN;
    setChatId(-1);
    setIsDeleted(false);
    endObjectChange();
    m_type = eVKContainerMessage;
}


VKContainerMessage::~VKContainerMessage()
{
}

void VKContainerMessage::completed() {
    Q_ASSERT(!isValid());
    Q_ASSERT(storage()->isContainsUser(m_user->id()));
    Q_ASSERT(!m_user->isValid());

    qDebug()<<"competing message"<<debugDescription();
    m_user = storage()->getUserById(m_user->id());
}

QSharedPointer<VKContainerMessage> VKContainerMessage::fromJson(VKStorage *storage, QJsonObject obj, QJsonArray users) {
    auto message = QSharedPointer<VKContainerMessage>(new VKContainerMessage(storage));
    message->beginObjectChange();


    QDateTime date;
    date.setTime_t(obj.value("date").toInt());
    message->setId(obj.value("id").toInt());
    message->setDate(date);
    message->setIsIncoming(obj.value("out").toInt() == 0);

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

    bool userFound = false;
    if (message->isIncoming()) {
        int id = obj.value("user_id").toInt();

        //better parse, because user data may be updated
        for (const auto &e : users) {
            auto el = e.toObject();
            if (el.value("id").toInt() == id) {
                auto user = VKContainerUser::fromJson(storage, el);
                message->setUser(user);
                storage->addUser(user);
                userFound = true;
                break;
            }
        }

        if (!userFound) {
            if (storage->isContainsUser(id)) {
                message->setUser(storage->getUserById(id));
            } else {
                message->setUser(QSharedPointer<VKContainerUser>(new VKContainerUser(storage)));
                message->user()->setId(id);
                message->user()->setInvalid();

                qDebug()<<"requesting additional user"<<message->user()->id()<<message->user()->isValid();
                auto handler = new VKHandlerUsers(storage);
                handler->setUsers({id});
                storage->helper()->request(message.data(), handler);
            }
        }
    } else {
        message->setUser(storage->getUserById(storage->ourUserId()));
    }

    message->setIsRead(obj.value("read_state").toInt() == 1);

    auto fwdMessages = obj.value("fwd_messages").toArray();
    for (auto e: fwdMessages) {
        auto fwd = e.toObject();
        auto msg = VKContainerMessage::fromJson(storage, fwd, users);
        msg->setIsIncoming(message->isIncoming());
        msg->setIsRead(message->isRead());
        message->addFwdMsg(msg);
    }
    qDebug()<<message->debugDescription();

    message->setAttachments( VKContainerAttachments::fromJson(storage, obj.value("attachments").toArray()));
    message->setAction(VKContainerMessageAction::fromJson(storage, obj, users));

    message->setValid(userFound);

    message->endObjectChange();
    return message;
}

bool VKContainerMessage::isRead() const {
    return m_readState == READ;
}


void VKContainerMessage::setUser(QSharedPointer<VKContainerUser> arg) {
    SET_ARG_NOCHECK(m_user, arg);
    QObject::connect(m_user.data(), &VKAbstractContainer::dataChanged, [this](VKAbstractContainer* ) {
        emit this->dataChanged(this);
    });
}

void VKContainerMessage::addFwdMsg(QSharedPointer<VKContainerMessage> arg) {
    arg->beginObjectChange();
    arg->setIsRead(isRead());
    arg->endObjectChange();
    m_fwd.append(arg);
}

void VKContainerMessage::setFwdMsg(int pos, QSharedPointer<VKContainerMessage> arg) {
    Q_ASSERT(pos < m_fwd.size());
    QObject::disconnect(m_fwd[pos].data(), SLOT(dataChanged(VKAbstractContainer*)));
    m_fwd[pos] = arg;
}

void VKContainerMessage::clearFwd() {
    m_fwd.clear();
}

void VKContainerMessage::setAttachments(QSharedPointer<VKContainerAttachments> attachments) {
    SET_ARG_NOCHECK(m_attachments, attachments);
}

void VKContainerMessage::setAction(QSharedPointer<VKContainerMessageAction> action) {
    SET_ARG_NOCHECK(m_action, action);
}

void VKContainerMessage::setIsRead(bool arg) {

    switch (m_readState) {
    case UNKNOWN:
        qDebug()<<"UNKNOWN";
        break;
    case READ:
        qDebug()<<"READ";
        break;
    case UNREAD:
        qDebug()<<"UNREAD";
        break;
    }
    qDebug()<<debugDescription();


    if (m_readState == READ && !arg) {
        m_readState = UNREAD;
        if (storage()->isContainsDialog(chatId())) {
            qDebug()<<"decreasing counter"<<chatId();
            auto dialog = storage()->getDialogById(chatId());
            dialog->setUnreadCount(dialog->unreadCount() + 1);
        }
    }
    if (m_readState == UNREAD  && arg) {
        m_readState = READ;
        if (storage()->isContainsDialog(chatId())) {
            qDebug()<<"increasing counter"<<chatId();
            auto dialog = storage()->getDialogById(chatId());
            dialog->setUnreadCount(dialog->unreadCount() - 1);
        }
    }

    if (m_readState == UNKNOWN) {
        if (arg) {
            m_readState = READ;
        } else {
            m_readState = UNREAD;
        }
    }

    for (auto e: m_fwd) {
        e->beginObjectChange();
        e->setIsRead(arg);
        e->endObjectChange();
    }
    emitChange();
}

void VKContainerMessage::processEmoji(QString &s) {

    VKEmojiParser parser;
    parser.parse(s);
}

void VKContainerMessage::createTemplateDialog() {

    auto dialog = QSharedPointer<VKContainerDialog>(new VKContainerDialog(storage()));

    qDebug()<<chatId()<<isChat();
    dialog->setUnreadCount(0);
    dialog->setId(chatId());
    dialog->setIsChat(isChat());
    if (isChat()) {
        dialog->setChatName(" ... ");
        auto chatIcon = QSharedPointer<VKContainerChatIcon>(new VKContainerChatIcon(storage()));
        chatIcon->add("https://vk.com/images/camera_50.png");
        dialog->setChatIcon(chatIcon);
        dialog->setInvalid();
    } else {
        dialog->setChatName(user()->userName());
        auto chatIcon = QSharedPointer<VKContainerChatIcon>(new VKContainerChatIcon(storage()));
        chatIcon->add(user()->iconMedium());
        dialog->setChatIcon(chatIcon);
        dialog->setValid();
    }

    storage()->addDialog(dialog, false);
}

bool VKContainerMessage::updateFrom(QSharedPointer<VKContainerMessage> message) {
    Q_ASSERT(id() == message->id());
    qDebug()<<debugDescription();

    bool updated = false;
    UPDATE_ARG_CHECK(message,   date,       setDate,        updated);
    UPDATE_ARG_CHECK(message,   isIncoming, setIsIncoming,  updated);
    UPDATE_ARG_CHECK(message,   body,       setBody,        updated);
    UPDATE_ARG_CHECK(message,   isChat,     setIsChat,      updated);
    UPDATE_ARG_CHECK(message,   chatId,     setChatId,      updated);
    UPDATE_ARG_CHECK(message,   isDeleted,  setIsDeleted,   updated);
    UPDATE_ARG_CHECK(message,   isRead,     setIsRead,      updated);

    qDebug()<<updated;

    //hack
    if (updated) {
        setUser(message->user());
        setAction(message->action());
        setAttachments(message->attachments());
        clearFwd();
        for (int i=0;i<message->countFwd();i++) {
            addFwdMsg(message->getFwd(i));
        }
    }

    return updated;
}

QString VKContainerMessage::debugDescription() {
    return QString("%1 %2 fwd count:%3").arg(body().mid(0,10)).arg(id()).arg(m_fwd.size());
}


int VKContainerMessage::countFwd() {
    return m_fwd.count();
}

QSharedPointer<VKContainerUser> VKContainerMessage::user() const {
    if (m_user.isNull()) {
        return QSharedPointer<VKContainerUser>(new VKContainerUser(storage()));
    }

    return m_user;
}

QSharedPointer<VKContainerAttachments> VKContainerMessage::attachments() const {
    if (m_attachments.isNull()) {
        return QSharedPointer<VKContainerAttachments>(new VKContainerAttachments(storage()));
    }

    return m_attachments;
}

QSharedPointer<VKContainerMessageAction> VKContainerMessage::action() const {
    if (m_action.isNull()) {
        return QSharedPointer<VKContainerMessageAction>(new VKContainerMessageAction(storage()));
    }

    return m_action;
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
    for (int i=0;i<countFwd();i++) {
        getFwd(i)->setIsIncoming(isIncoming());
    }
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

void VKContainerMessage::setIsDeleted(bool arg) {
    SET_ARG(m_isDeleted, arg);
    qDebug()<<"deleted changed"<<arg;
    emit deleted(this);
}

