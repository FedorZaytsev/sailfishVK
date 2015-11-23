#include "vklpmessagenew.h"
#include "vkhandlerdialogbyid.h"
#include "vkhandlermessagebyid.h"
#include "vkhandlerusers.h"

VKLPMessageNew::VKLPMessageNew(VKStorage *storage, QObject *parent) :
    VKLPAbstract(storage, parent)
{
    m_id = 0;
    m_isChat = false;
    m_addDialog = false;
    m_userId = 0;
    m_type = VKLPEventType::MESSAGE_NEW;
}

void VKLPMessageNew::fromLP(const QJsonArray &data) {
    Q_UNUSED(data);

    bool requestingDialog = false;
    bool requestingMessage = false;
    bool requestingUser = false;
    m_message = QSharedPointer<VKContainerMessage>(new VKContainerMessage(storage()));

    m_message->setId(data.at(1).toInt());
    VKLPFlags flags(data.at(2).toInt());
    m_message->setIsDeleted(flags.isSet(VKLPFlags::DELETED));
    m_message->setIsIncoming(!flags.isSet(VKLPFlags::OUTBOX));
    m_message->setIsRead(!flags.isSet(VKLPFlags::UNREAD));
    int fromId = data.at(3).toInt();
    if (fromId < MAX_USER_ID) {
        m_message->setChatId(fromId);
        m_message->setIsChat(false);
        if (m_message->isIncoming()) {
            if (storage()->isContainsUser(fromId)) {
                m_message->setUser(storage()->getUserById(fromId));
            } else {
                auto handler = new VKHandlerUsers(storage());
                handler->setUsers({fromId});
                storage()->helper()->request(this, handler);
            }
        } else {
            m_message->setUser(storage()->getUserById(storage()->ourUserId()));
        }
        if (!storage()->isContainsDialog(fromId)) {
            requestingDialog = true;
            qDebug()<<"new message in new chat";

            auto handler = new VKHandlerDialogById(storage());
            handler->add(m_message->id());
            storage()->helper()->request(this, handler);

        }

    } else {
        m_message->setChatId(fromId - MAX_USER_ID);
        m_message->setIsChat(true);
        if (!storage()->isContainsDialog(m_message->chatId())) {
            requestingDialog = true;
            qDebug()<<"new message in new chat";

            auto handler = new VKHandlerDialogById(storage());
            handler->add(m_message->id());
            storage()->helper()->request(this, handler);
        }


        Q_ASSERT(data.at(7).isObject() && data.at(7).toObject().contains("from"));
        int idx = data.at(7).toObject().value("from").toString().toInt();

        if (storage()->isContainsUser(idx)) {
            qDebug()<<"user is found";
            m_message->setUser(storage()->getUserById(idx));
        } else {
            qDebug()<<"user not found";
            requestingUser = true;
            //users.append(QString::number(idx));

            auto handler = new VKHandlerUsers(storage());
            handler->setUsers({idx});
            storage()->helper()->request(this, handler);

            auto usr = QSharedPointer<VKContainerUser>(new VKContainerUser(storage()));
            usr->setId(idx);
            usr->setValid(false);
            m_message->setUser(usr);
        }
    }


    if (data.size() > 7 && data.at(7).isObject()) {
        QJsonObject attachments = data.at(7).toObject();
        if (attachments.contains("fwd")) {
            qDebug()<<"have fwd. Requesting";
            requestingMessage = true;

            auto handler = new VKHandlerMessageById(storage());
            handler->add(m_message->id());
            storage()->helper()->request(this, handler);

            //msgs.append(QString::number(m_message->id()));

            //because of f*cking VKontakte developers, an attachments parser doesn't work anymore
            //(message id is not valid)
            //so just request full message in this case


            /*VKLongPollUpdateParser parser;
            parser.parse(attachments.value("fwd").toString());


            auto fwdTop = parser.topMessages();
            qDebug()<<fwdTop;
            for (auto &e: fwdTop) {
                if (!storage()->isContainsMessage(e)) {
                    requestingMessage = true;
                    msgs.append(QString::number(e));
                    auto m = QSharedPointer<VKContainerMessage>(new VKContainerMessage(storage()));
                    m->setId(e);
                    m->setValid(false);
                    m_message->addFwdMsg(m);
                    qDebug()<<"need additional data because of fwd";
                } else {
                    m_message->addFwdMsg(storage()->getMessageById(e));
                }
            }*/
        }


        //FIX IT
        //fix it. It is too mush to request full message insted of one (or more) attachments directly
        //have attachments
        if (attachments.contains("attach1")) {
            qDebug()<<"have attachments, so requesting full dialog";
            requestingMessage = true;

            auto handler = new VKHandlerMessageById(storage());
            handler->add(m_message->id());
            storage()->helper()->request(this, handler);
            //msgs.append(QString::number(m_message->id()));
        }
        if (attachments.contains("source_act")) {
            qDebug()<<"have source act";
            QJsonObject obj;
            obj.insert("action", attachments.value("source_act").toString());
            obj.insert("action_text", attachments.value("source_text").toString());
            if (attachments.value("source_mid").isString()) {
                obj.insert("action_mid", attachments.value("source_mid").toString().toInt());
            } else {
                obj.insert("action_mid", attachments.value("source_mid").toInt());
            }
            m_message->setAction(VKContainerMessageAction::fromJson(storage(), obj, QJsonArray()));
        }
    }




    QDateTime date;
    date.setTime_t(data.at(4).toInt());
    m_message->setDate(date);
    m_message->setBody(data.at(6).toString());

    m_valid = !(requestingDialog || requestingMessage || requestingUser);

    if (!requestingDialog) {
        qDebug()<<"New message recieved"<<m_message->isRead();
        storage()->addMessage(m_message);
        if (!m_message->isRead()) {
            auto dialog = storage()->getDialogById(m_message->chatId());
            dialog->setUnreadCount( dialog->unreadCount() + 1 );
            qDebug()<<"emit dialog change";
            dialog->emitChange();
        }
    } else {
        m_addDialog = true;
    }

    if (m_valid) {
        deleteLater();
    }

}

void VKLPMessageNew::completed() {

    if (m_addDialog) {
        qDebug()<<"adding dialog";
        storage()->addMessage(m_message);
    }

    if (!m_message->user()->isValid()) {
        qDebug()<<"invalid user";
        if (storage()->isContainsUser(m_message->user()->id())) {
            qDebug()<<"setting user";
            m_message->setUser(storage()->getUserById(m_message->user()->id()));
            Q_ASSERT(storage()->isContainsDialog(m_message->chatId()));

            auto dialog = storage()->getDialogById(m_message->chatId());
            if (dialog->firstMessage()->id() == m_message->id()) {
                dialog->emitChange();
            }
        }
    }
    deleteLater();
}
