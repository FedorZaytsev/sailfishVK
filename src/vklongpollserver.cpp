#include "vklongpollserver.h"
#include "vklongpollupdateparser.h"
#include "vkhandlerlongpollupdatedata.h"
#include "vk.h"

VKLongPollServer::VKLongPollServer(VKStorage* storage, QObject *parent) :
    VKAbstractHandler(storage, parent)
{
    m_vk = NULL;
    setStorage(0);
    setVK(0);
    setTs(0);
    setPts(0);
    QObject::connect(&m_manager, &QNetworkAccessManager::finished, this, &VKLongPollServer::networkDataReady);
}

void VKLongPollServer::init(VK* vk, VKStorage* storage, QString key, QString server, int ts, int pts) {
    setKey(key);
    setServer(server);
    setTs(ts);
    setPts(pts);
    setStorage(storage);
    setVK(vk);

    request();
    qDebug()<<"initialized";
}

void VKLongPollServer::request() {
    QUrl url(QString("https://%1?act=a_check&key=%2&ts=%3&wait=25&mode=2").arg(server()).arg(key()).arg(ts()));

    qDebug()<<url.toString();

    m_manager.get(QNetworkRequest(url));
}

void VKLongPollServer::processUpdate(QJsonArray &update) {
    int type = update.at(0).toInt();
    qDebug()<<"type"<<type;
    QList<QString> userIds;
    QList<QString> messageIds;
    switch (type) {
        case VKLongPollServer::VKUPDATE_MESSAGE_NEW: {
            qDebug()<<"new message";
            int id = update.at(1).toInt();
            messageIds.append(QString::number(id));
            int flags = update.at(2).toInt();
            int fromId = update.at(3).toInt();
            QString body = update.at(5).toString();
            QJsonObject attachments = update.at(7).toObject();

            int fromUser = 0;
            if (attachments.value("from").isDouble()) {
                fromUser = attachments.value("from").toInt();
            }
            qDebug()<<"message from"<<fromId<<"id"<<id;
            if (attachments.value("fwd").isString()) {
                VKLongPollUpdateParser parser;
                parser.parse(attachments.value("fwd").toString());

                userIds.append(parser.uniqueUsers());
            } else {
                if (storage()->userExist(fromId)) {
                    VKContainerMessage* message = new VKContainerMessage;
                    message->setMsgId(id);
                    QDateTime date;
                    date.setTime_t(update.at(4).toInt());
                    message->setDate(date);
                    message->setIsIncoming(flags & 2);
                    message->setReadState(flags & 1);
                    message->setBody(body);
                    message->setIsChat(fromId > 2000000000);
                    VKContainerUser* user = new VKContainerUser;
                    user->setId(fromUser);
                    message->setUser(user);
                    if (fromId > 2000000000) {
                        message->setChatId(fromId - 2000000000);
                    } else {
                        message->setChatId(fromId);
                    }
                }
            }
        } break;
        default: {
        }
    }
    qDebug()<<"LongPoll request users"<<userIds<<"and messages"<<messageIds;
    if (messageIds.length()) {
        m_updateData = new VKHandlerLongPollUpdateData(storage(), this);
        QObject::connect(m_updateData, &VKHandlerLongPollUpdateData::dataReady, this, &VKLongPollServer::updateDataReady);
        m_updateData->setUserIds(userIds);
        m_updateData->setMsgIds(messageIds);
        m_vk->sendNetworkRequest(m_updateData);
    }
}

void VKLongPollServer::updateDataReady() {
    QJsonObject data = m_updateData->data();

    for (auto e : data) {
        auto message = e.toObject();
        QJsonObject dialog;
        if (message.contains("chat_id")) {
            dialog.insert("unread", storage()->getUnread(message.value("chat_id").toInt()) + 1);
        } else {
            dialog.insert("unread", storage()->getUnread(message.value("user_id").toInt()) + 1);

        }
        dialog.insert("message", message);
        VKContainerDialog* parsedDialog = VKContainerDialog::fromJson(storage(), dialog, data.value("users").toArray());
        m_data.append(parsedDialog);
    }

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
            for (auto e : updates) {
                auto el = e.toArray();
                processUpdate(el);
            }

        } else {
            qDebug()<<"no update field";
        }
        if (object.value("ts").isDouble()) {
            setTs(object.value("ts").toInt());
            request();
        }
    } else {
        qCritical()<<"Reply error"<<reply->errorString();
        Q_ASSERT(0);
    }
}
