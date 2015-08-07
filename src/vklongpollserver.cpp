

#include "vklongpollserver.h"
#include "vklongpollupdateparser.h"
#include "vkhandlerlongpollupdatedata.h"
#include "vk.h"

VKLongPollServer::VKLongPollServer(VKStorage* storage, QObject *parent) :
    VKAbstractHandler(storage, parent)
{
    m_vk = NULL;
    m_initialized = false;
    setStorage(0);
    setVK(0);
    setTs(0);
    setPts(0);
    QObject::connect(&m_manager, &QNetworkAccessManager::finished, this, &VKLongPollServer::networkDataReady);

    m_longPollData[VKLPEventType::MESSAGE_DELETE] = {};
    m_longPollData[VKLPEventType::CHAT_UPDATED] = {};
    m_longPollData[VKLPEventType::CHAT_USER_TYPING] = {};
    m_longPollData[VKLPEventType::COUNTER_UPDATE] = {};
    m_longPollData[VKLPEventType::MESSAGE_FLAGS_CHANGE] = {};
    m_longPollData[VKLPEventType::MESSAGE_FLAGS_RESET] = {};
    m_longPollData[VKLPEventType::MESSAGE_FLAGS_SET] = {};
    m_longPollData[VKLPEventType::MESSAGE_MARK_READ_INCOMING] = {};
    m_longPollData[VKLPEventType::MESSAGE_MARK_READ_OUTCOMING] = {};
    m_longPollData[VKLPEventType::USER_OFFLINE] = {};
    m_longPollData[VKLPEventType::USER_ONLINE] = {};
    m_longPollData[VKLPEventType::USER_TYPING] = {};
    m_longPollData[VKLPEventType::VIDEOCALL] = {};
}

void VKLongPollServer::init(VK* vk, VKStorage* storage) {
    setStorage(storage);
    setVK(vk);

    request();
    m_initialized = true;
    qDebug()<<"initialized";
}

int VKLongPollServer::count() {
    return m_readyEvents.count();
}

VKLPAbstract *VKLongPollServer::at(int idx) {
    return m_readyEvents.at(idx);
}

void VKLongPollServer::clean() {
    m_readyEvents.clear();
}

void VKLongPollServer::request() {
    //mode 66 = 64+2 = return user device + attachments
    QUrl url(QString("https://%1?act=a_check&key=%2&ts=%3&wait=25&mode=66").arg(server()).arg(key()).arg(ts()));

    qDebug()<<url.toString();

    m_manager.get(QNetworkRequest(url));
}

void VKLongPollServer::processUpdate(QJsonArray &update,
                                     QList<QString> &userIds,
                                     QList<QString> &messageIds,
                                     QList<QString> &chatIds,
                                     QList<QString> &checkMessages,
                                     QList<QString> &removed) {
    VKLPAbstract* e = NULL;

    int type = update.at(0).toInt();
    switch (type) {
    case VKLPEventType::MESSAGE_DELETE: {
        //possible memory leak
        auto event = new VKLPMessageDelete(this);
        event->fromLP(update, checkMessages);
        e = event;
    } break;
    case VKLPEventType::MESSAGE_FLAGS_CHANGE: {
        auto event = new VKLPMessageFlagsChange(this);
        event->fromLP(update);
        e = event;
    } break;
    case VKLPEventType::MESSAGE_FLAGS_RESET: {
        auto event = new VKLPMessageFlagsReset(this);
        event->fromLP(update, removed);
        e = event;
    } break;
    case VKLPEventType::MESSAGE_FLAGS_SET: {
        auto event = new VKLPMessageFlagsSet(this);
        event->fromLP(update, checkMessages);
        e = event;
    } break;
    case VKLPEventType::MESSAGE_NEW: {
        auto event = new VKLPMessageNew(this);
        event->fromLP(update, messageIds, userIds, chatIds);
        e = event;
    } break;
    case VKLPEventType::MESSAGE_MARK_READ_INCOMING: {
        auto event = new VKLPMessageMarkIncoming(this);
        event->fromLP(update);
        e = event;
    } break;
    case VKLPEventType::MESSAGE_MARK_READ_OUTCOMING: {
        auto event = new VKLPMessageMarkOutcoming(this);
        event->fromLP(update);
        e = event;
    } break;
    case VKLPEventType::USER_OFFLINE: {
        auto event = new VKLPUserOffline(this);
        event->fromLP(update);
        e = event;
    } break;
    case VKLPEventType::USER_ONLINE: {
        auto event = new VKLPUserOnline(this);
        event->fromLP(update);
        e = event;
    } break;
    case VKLPEventType::CHAT_UPDATED: {
        auto event = new VKLPChatUpdated(this);
        event->fromLP(update);
        e = event;
    } break;
    case VKLPEventType::USER_TYPING: {
        auto event = new VKLPUserTyping(this);
        event->fromLP(update, userIds);
        e = event;
    } break;
    case VKLPEventType::CHAT_USER_TYPING: {
        auto event = new VKLPChatUserTyping(this);
        event->fromLP(update, userIds);
        e = event;
    } break;
    case VKLPEventType::COUNTER_UPDATE:  {
        auto event = new VKLPCounterUpdate(this);
        event->fromLP(update);
        e = event;
    } break;
    case 101: {
    } break;
    case 114: {
    } break;
    default: {
        qDebug()<<"unknown update idx"<<type;
        Q_ASSERT(0);
    } break;
    }

    if (e) {
        qDebug()<<"event is valid?"<<e->isValid();
        if (e->isValid()) {
            m_readyEvents.push_back(e);
        } else {
            m_cachedEvents[e->type()].push_back(e);
        }
    }
}

void VKLongPollServer::sendUpdateDataRequest(QList<QString> &userIds,
                                             QList<QString> &messageIds,
                                             QList<QString> &chatIds,
                                             QList<QString> &checkMessages,
                                             QList<QString> &removed) {
    auto updateData = new VKHandlerLongPollUpdateData(storage(), this);
    QObject::connect(updateData, &VKHandlerLongPollUpdateData::ready, this, &VKLongPollServer::updateDataReady);

    updateData->setUserIds(userIds);
    updateData->setMsgIds(messageIds);
    updateData->setChatIds(chatIds);
    updateData->setCheckIds(checkMessages);
    updateData->setRemoved(removed);
    vk()->sendNetworkRequest(updateData);
}

QString VKLongPollServer::type2string(VKLPEventType::E_VKUPDATE type) {
    switch (type) {
    case VKLPEventType::CHAT_UPDATED:
        return "CHAT_UPDATED";
    case VKLPEventType::CHAT_USER_TYPING:
        return "CHAT_USER_TYPING";
    case VKLPEventType::COUNTER_UPDATE:
        return "COUNTER_UPDATE";
    case VKLPEventType::MESSAGE_DELETE:
        return "MESSAGE_DELETE";
    case VKLPEventType::MESSAGE_FLAGS_CHANGE:
        return "MESSAGE_FLAGS_CHANGE";
    case VKLPEventType::MESSAGE_FLAGS_RESET:
        return "MESSAGE_FLAGS_RESET";
    case VKLPEventType::MESSAGE_FLAGS_SET:
        return "MESSAGE_FLAGS_SET";
    case VKLPEventType::MESSAGE_MARK_READ_INCOMING:
        return "MESSAGE_MARK_READ_INCOMING";
    case VKLPEventType::MESSAGE_MARK_READ_OUTCOMING:
        return "MESSAGE_MARK_READ_OUTCOMING";
    case VKLPEventType::MESSAGE_NEW:
        return "MESSAGE_NEW";
    case VKLPEventType::USER_OFFLINE:
        return "USER_OFFLINE";
    case VKLPEventType::USER_ONLINE:
        return "USER_ONLINE";
    case VKLPEventType::USER_TYPING:
        return "USER_TYPING";
    case VKLPEventType::VIDEOCALL:
        return "VIDEOCALL";
    default:
        return QString("UNKNOWN_%1").arg(type);
    }
}

void VKLongPollServer::updateDataReady(VKAbstractHandler *handler) {

    qDebug()<<"ready, updating";

    QJsonObject data = handler->data().toObject();
    auto messages = data.value("messages").toObject().value("items").toArray();
    auto users = data.value("users").toArray();
    auto checkMsgs = data.value("check").toArray();
    auto checkUsers = data.value("checkUsers").toArray();
    auto removedMsgs = data.value("removed").toArray();
    auto removedUsers = data.value("removedUsers").toArray();

    QVector<int> unknownUsers;
    for (auto e : messages) {
        auto dialog = e.toObject();
        VKContainerDialog* dlg = VKContainerDialog::fromJson(storage(), dialog, users, unknownUsers);
        qDebug()<<"new dialog"<<dlg->chatName()<<dlg->chatId()<<dlg->message()->msgId();
        dlg->setParent(this);
        m_updateDialogs.append(dlg);
    }

    for (auto e : checkMsgs) {
        auto message = e.toObject();
        VKContainerMessage* msg = VKContainerMessage::fromJson(storage(), message, checkUsers, unknownUsers);
        qDebug()<<"new message"<<msg->msgId()<<msg->body().mid(0,10);
        msg->setParent(this);
        m_updateMessages.append(msg);
    }

    for (auto e : removedMsgs) {
        auto message = e.toObject();
        VKContainerMessage* msg = VKContainerMessage::fromJson(storage(), message, removedUsers, unknownUsers);
        qDebug()<<"new message"<<msg->msgId()<<msg->body().mid(0,10);
        msg->setParent(this);
        m_updateMessages.append(msg);
    }

    for (auto e : users) {
        auto user = e.toObject();
        VKContainerUser* usr = VKContainerUser::fromJson(storage(), user);
        qDebug()<<"new user"<<usr->id()<<usr->firstName()<<usr->lastName();
        usr->setParent(this);
        m_updateUsers.append(usr);
    }

    if (!unknownUsers.length()) {
        updateReadyEvents();
    } else {
        QStringList lst;
        for (auto e: unknownUsers) {
            lst.append(QString::number(e));
        }

        //Additional request for case when we don't have info about users in fwd messages
        qDebug()<<"We need additional users info about"<<lst.join(",");
        auto handlerUsers = new VKHandlerUsers(storage(), this);
        QObject::connect(handlerUsers, &VKHandlerUsers::ready, this, &VKLongPollServer::additionalInformationAboutUsersReady);
    }

    handler->deleteLater();
}

void VKLongPollServer::additionalInformationAboutUsersReady(VKAbstractHandler *h) {

    auto handler = dynamic_cast<VKHandlerUsers*>(h);

    for (auto e: m_updateDialogs) {
        for (int i=0;i<handler->count();i++) {
            auto el = handler->get(i);
            if (e->message()->user()->id() == el->id()) {
                delete e->message()->user();
                e->message()->setUser(el);
            }
        }
    }

    for (auto e: m_updateMessages) {
        for (int i=0;i<handler->count();i++) {
            auto el = handler->get(i);
            if (e->user()->id() == el->id()) {
                delete e->user();
                e->setUser(el);
            }
        }
    }

    updateReadyEvents();
    handler->deleteLater();
}

void VKLongPollServer::updateReadyEvents() {

    qDebug()<<"m_updateDialogs.count()"<<m_updateDialogs.count();
    for (auto e: m_updateDialogs) {
        qDebug()<<e->message()->msgId()<<e->message()->body().mid(0,15);
    }
    qDebug()<<"----";

    qDebug()<<"m_updateMessages.count()"<<m_updateMessages.count();
    for (auto e: m_updateMessages) {
        qDebug()<<e->msgId()<<e->user()->lastName();
    }
    qDebug()<<"----";

    qDebug()<<"m_updateUsers.count()"<<m_updateUsers.count();
    for (auto e: m_updateUsers) {
        qDebug()<<e->id()<<e->firstName()<<e->lastName();
    }
    qDebug()<<"----";


    for (auto k : m_cachedEvents.keys()) {
        qDebug()<<"log test"<< m_cachedEvents[k].count();
        auto &v = m_cachedEvents[k];
        for (int i=v.size()-1;i>=0;i--) {
            auto e = v[i];
            e->complete(m_updateDialogs, m_updateMessages, m_updateUsers);
            if (e->isValid()) {
                m_readyEvents.append(e);
                v.remove(i);
                qDebug()<<"deleting this element";
            }
        }
        qDebug()<<"log test end"<< m_cachedEvents[k].count();
    }
    m_updateDialogs.clear();
    m_updateMessages.clear();
    m_updateUsers.clear();


    qDebug()<<"emit ready";
    vk()->sendContainersToScript(this);
}

void VKLongPollServer::networkDataReady(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QString data = reply->readAll();

        qDebug()<<data;

        QJsonParseError err;
        QJsonDocument document = QJsonDocument::fromJson(data.toUtf8(), &err);
        if (err.error != QJsonParseError::NoError) {
            qFatal("%s",err.errorString().toUtf8().data());
        }
        QJsonObject object = document.object();
        if (object.value("updates").isArray()) {
            QJsonArray updates = object.value("updates").toArray();
            QList<QString> userIds, messageIds, chatIds, checkMessages, removed;
            for (auto e : updates) {
                auto el = e.toArray();
                processUpdate(el, userIds, messageIds, chatIds, checkMessages, removed);
            }
            qDebug()<<"LongPoll request users"<<userIds<<"and messages"<<messageIds<<"chatIds"<<chatIds<<"checkMessages"<<checkMessages<<"removed"<<removed;
            if (userIds.length() || messageIds.length() || chatIds.length() || checkMessages.length() || removed.length()) {
                sendUpdateDataRequest(userIds, messageIds, chatIds, checkMessages, removed);
            }
            if (m_readyEvents.length()) {
                vk()->sendContainersToScript(this);
            }
            qDebug()<<"sent request";
        } else {
            qDebug()<<"no update field";
        }
        if (object.contains("ts")) {
            setTs(object.value("ts").toInt());
            request();
        }
        if (object.contains("failed")) {
            int val = object.value("failed").toInt();
            switch (val) {
            case VKLP_REFRESH_HISTORY: {
                emit updatePages();
                setTs(object.value("ts").toInt());
                qDebug()<<"VKLP_REFRESH_HISTORY";
            } break;
            case VKLP_REFRESH_KEY: {
                vk()->startLongPollServer(false);
                qDebug()<<"VKLP_REFRESH_KEY";
            } break;
            case VKLP_REFRESH_KEY_AND_HISTORY: {
                emit updatePages();
                vk()->startLongPollServer(true);
                qDebug()<<"VKLP_REFRESH_KEY_AND_HISTORY";
            } break;
            }
        }
    } else {
        qCritical()<<"Reply error"<<reply->errorString();
        Q_ASSERT(0);
    }
}
