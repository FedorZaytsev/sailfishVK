

#include "vklongpollserver.h"
#include "vklongpollupdateparser.h"
#include "vkhandlerlongpollupdatedata.h"
#include "vk.h"

VKLongPollServer::VKLongPollServer(VKStorage* storage, QObject *parent) :
    QObject(parent)
{
    m_storage = storage;
    m_vk = NULL;
    m_initialized = false;
    setStorage(0);
    setVK(0);
    setTs(0);
    setPts(0);
    QObject::connect(&m_manager, &QNetworkAccessManager::finished, this, &VKLongPollServer::networkDataReady);

    m_timer.setInterval(TIMEOUT_REQUEST);
    m_timer.setSingleShot(false);
    QObject::connect(&m_timer, &QTimer::timeout, this, &VKLongPollServer::watchdogTimer);
    m_timer.start();

    m_lastTime = QDateTime::currentDateTimeUtc();
}

void VKLongPollServer::init(VK* vk, VKStorage* storage) {
    setStorage(storage);
    setVK(vk);

    forceRequest();
    m_initialized = true;
    qDebug()<<"initialized";
}

void VKLongPollServer::forceRequest() {
    //mode 66 = 64+2 = return user device + attachments
    QUrl url(QString("https://%1?act=a_check&key=%2&ts=%3&wait=25&mode=66").arg(server()).arg(key()).arg(ts()));

    qDebug()<<url.toString();

    m_lastTime = QDateTime::currentDateTimeUtc();

    m_manager.get(QNetworkRequest(url));
}

void VKLongPollServer::processUpdate(QJsonArray &update/*,
                                     QList<QString> &userIds,
                                     QList<QString> &messageIds,
                                     QList<QString> &chatIds,
                                     QList<QString> &checkMessages,
                                     QList<QString> &removed,
                                     QVector<QSharedPointer<VKLPAbstract>> &cached*/) {
    VKLPAbstract* e;

    //checkMessages - getting previous message
    //removed - getting message with constant id
    //userIds - getting user
    //messageIds - getting messags
    //chatIds - getting dialogs

    int type = update.at(0).toInt();
    switch (type) {
    case VKLPEventType::MESSAGE_DELETE: {
        auto event = new VKLPMessageDelete(storage(), this);
        event->fromLP(update);
        e = event;
    } break;
    case VKLPEventType::MESSAGE_FLAGS_CHANGE: {
        auto event = new VKLPMessageFlagsChange(storage(), this);
        event->fromLP(update);
        e = event;
    } break;
    case VKLPEventType::MESSAGE_FLAGS_RESET: {
        auto event = new VKLPMessageFlagsReset(storage(), this);
        event->fromLP(update);
        e = event;
    } break;
    case VKLPEventType::MESSAGE_FLAGS_SET: {
        auto event = new VKLPMessageFlagsSet(storage(), this);
        event->fromLP(update);
        e = event;
    } break;
    case VKLPEventType::MESSAGE_NEW: {
        auto event = new VKLPMessageNew(storage(), this);
        event->fromLP(update);
        e = event;
    } break;
    case VKLPEventType::MESSAGE_MARK_READ_INCOMING: {
        auto event = new VKLPMessageMarkIncoming(storage(), this);
        event->fromLP(update);
        e = event;
    } break;
    case VKLPEventType::MESSAGE_MARK_READ_OUTCOMING: {
        auto event = new VKLPMessageMarkOutcoming(storage(), this);
        event->fromLP(update);
        e = event;
    } break;
    case VKLPEventType::USER_OFFLINE: {
        auto event = new VKLPUserOffline(storage(), this);
        event->fromLP(update);
        e = event;
    } break;
    case VKLPEventType::USER_ONLINE: {
        auto event = new VKLPUserOnline(storage(), this);
        event->fromLP(update);
        e = event;
    } break;
    case VKLPEventType::CHAT_UPDATED: {
        auto event = new VKLPChatUpdated(storage(), this);
        event->fromLP(update);
        e = event;
    } break;
    case VKLPEventType::USER_TYPING: {
        auto event = new VKLPUserTyping(storage(), this);
        event->fromLP(update);
        e = event;
    } break;
    case VKLPEventType::CHAT_USER_TYPING: {
        auto event = new VKLPChatUserTyping(storage(), this);
        event->fromLP(update);
        e = event;
    } break;
    case VKLPEventType::COUNTER_UPDATE:  {
        auto event = new VKLPCounterUpdate(storage(), this);
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

    Q_UNUSED(e);

    /*if (!e.isNull()) {
        if (!e->isValid()) {
            cached.push_back(e);
        }
    }*/

    //if (e) {
        //if (e->isValid()) {
        //    m_readyEvents.push_back(e);
        //} //else {
            //m_cachedEvents[e->type()].push_back(e);
        //}
    //}
}

void VKLongPollServer::sendUpdateDataRequest(QList<QString> &userIds,
                                             QList<QString> &messageIds,
                                             QList<QString> &chatIds,
                                             QList<QString> &checkMessages,
                                             QList<QString> &removed,
                                             QVector<QSharedPointer<VKLPAbstract> > &cached) {
    auto updateData = new VKHandlerLongPollUpdateData(storage(), this);
    QObject::connect(updateData, &VKHandlerLongPollUpdateData::ready, this, &VKLongPollServer::updateDataReady);

    updateData->setUserIds(userIds);
    updateData->setMsgIds(messageIds);
    updateData->setChatIds(chatIds);
    updateData->setCheckIds(checkMessages);
    updateData->setRemoved(removed);
    updateData->setEvents(cached);
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

void VKLongPollServer::updateDataReady(VKAbstractHandler *h) {

    auto* handler = dynamic_cast<VKHandlerLongPollUpdateData*>(h);

    auto& dialogs = handler->dialogs();
    auto& messages = handler->messages();
    auto& users = handler->users();
    auto events = handler->events();

    qDebug()<<"Dialogs:";
    for (auto dialog: dialogs) {
        qDebug()<<"     "<<dialog->chatName();
    }
    qDebug()<<"Messages:";
    for (auto message: messages) {
        qDebug()<<"     "<<message->id()<<message->body().mid(0,15);
    }
    qDebug()<<"Users:";
    for (auto user: users) {
        qDebug()<<"     "<<user->firstName()<<user->lastName();
    }

    for (auto e: events) {
        e->complete(dialogs, messages, users);
    }

    handler->deleteLater();
}

void VKLongPollServer::watchdogTimer() {

    if (m_lastTime.msecsTo(QDateTime::currentDateTimeUtc()) > TIMEOUT_REQUEST) {
        qDebug()<<"LongPoll error, restart by watch dog";
        forceRequest();
    }

}

/*
void VKLongPollServer::updateReadyEvents(QVector<QSharedPointer<VKLPAbstract>> events) {

    qDebug()<<"m_updateDialogs.count()"<<m_updateDialogs.count();
    for (auto e: m_updateDialogs) {
        storage()->addDialog(e);
        qDebug()<<e->id()<<e->chatName();
    }
    qDebug()<<"----";

    qDebug()<<"m_updateMessages.count()"<<m_updateMessages.count();
    for (auto e: m_updateMessages) {
        storage()->addMessage(e);
        qDebug()<<e->id()<<e->user()->lastName();
    }
    qDebug()<<"----";

    qDebug()<<"m_updateUsers.count()"<<m_updateUsers.count();
    for (auto e: m_updateUsers) {
        storage()->addUser(e);
        qDebug()<<e->id()<<e->firstName()<<e->lastName();
    }
    qDebug()<<"----";


    for (auto k : m_cachedEvents.keys()) {
        qDebug()<<"m_cachedEvents.count()"<< m_cachedEvents[k].count()<<k;
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
        qDebug()<<"m_cachedEvents.count() end"<< m_cachedEvents[k].count();
    }
    m_updateDialogs.clear();
    m_updateMessages.clear();
    m_updateUsers.clear();


    qDebug()<<"emit ready";
    vk()->sendHandlertoScript(this);
}
*/

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

            for (auto e : updates) {
                auto el = e.toArray();
                processUpdate(el/*, userIds, messageIds, chatIds, checkMessages, removed, cached*/);
            }
        } else {
            qDebug()<<"no update field";
        }
        if (object.contains("ts")) {
            setTs(object.value("ts").toInt());
            forceRequest();
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
            m_vk->displayErrorMessage("Restarting long poll server", VK::ERROR_HANDLER_INFORM);
        }
    } else {
        qCritical()<<"Reply error"<<reply->errorString();
        forceRequest();
    }
}
