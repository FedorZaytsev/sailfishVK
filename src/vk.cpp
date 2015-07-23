#include "vk.h"
#include "vkpixmapprovider.h"
#include "vklongpollserver.h"
#include "vklongpollupdateparser.h"

VK* __vk_object = NULL;

//todo https://vk.com/dev/api_nohttps
//todo VK::ERROR_CAPTHA
//todo VK::ERROR_HTTPS_SAME
//todo VK::ERROR_NEED_CONFORMATION

VK::VK(QObject *parent) :
    QObject(parent)
{
    if (__vk_object) {
        qFatal("cannot create more than one VK object");
    } else {
        __vk_object = this;
    }

    m_manager = new QNetworkAccessManager(this);
    QObject::connect(m_manager, &QNetworkAccessManager::finished, this, &VK::requestFinished);
    QDir dir = QDir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)).filePath(QCoreApplication::applicationName());

    if (!dir.exists()) {
        dir.mkpath(".");
    }
    QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, dir.path());

    m_VKStorage.init();
    QObject::connect(&m_VKStorage, &VKStorage::error, this, &VK::storageError);

    m_longPoll = new VKLongPollServer(&m_VKStorage, this);
}

VK::~VK() {
    m_settings.sync();
}

void VK::storageError(QString msg) {
    qDebug()<<"Storage error"<<msg;
}

void VK::timerRequest(VKAbstractHandler *handler) {
    Q_ASSERT(handler);

    qDebug()<<"Restart request"<<handler->name();

    sendNetworkRequest(handler);
}

void VK::sendHandlertoScript(VKAbstractHandler *handler) {
    sendContainersToScript(handler);
}

void VK::processHandler(VKAbstractHandler *handler) {
    sendNetworkRequest(handler);
}

void VK::displayErrorMessage(QString err, ErrorHandlers displayType) {
    //Q_UNUSED(displayType);
    //qDebug()<<"ERROR:"<<err;
    //qFatal("VK::displayErrorMessage not implemented");
    static bool flag;
    if (!flag) {
        flag = true;
        emit displayError(err, displayType);
    }
}

QString VK::getAuthPageUrl() {
    return "https://oauth.vk.com/authorize?"
                                "client_id=4765582"
                                "&scope=offline,messages,friends,notify"
                                "&redirect_uri=https://oauth.vk.com/blank.html"
                                "&display=mobile"
                                "&v=5.28"
                                "&response_type=token";
}

void VK::downloadImageToCache(QString url) {
    m_manager->get(QNetworkRequest(url));
}

void VK::sendContainersToScript(VKAbstractHandler* handler) {
    qDebug()<<"sendContainersToScript";
    emit handlerReady(handler->name(),  handler);
}

bool VK::updateAccessToken(QString str_url) {
    QUrl url(str_url);

    qDebug()<<"host"<<url.host()<<"fragment"<<url.fragment()<<"path"<<url.path();

    if (url.host() == "oauth.vk.com" && url.path() == "/blank.html") {
        QUrlQuery query(url.fragment());
        Q_ASSERT(query.queryItemValue("expires_in") == "0");
        m_VKStorage.setAccessToken(query.queryItemValue("access_token"));
        m_VKStorage.setOurUserId(query.queryItemValue("user_id").toInt());
        return true;
    }
    return false;
}



void VK::getDialogs(int offset) {
    //Q_ASSERT(0);
    qDebug()<<"VK::getDialogs offset"<<offset;
    Q_ASSERT(initialized());

    VKHandlerDialogs* dialogHandler = new VKHandlerDialogs(&storage(), this);
    dialogHandler->setOffset(offset);
    dialogHandler->setLongPoll(!m_longPoll->initilized());
    QObject::connect(dialogHandler, &VKAbstractHandler::ready, this, &VK::sendHandlertoScript);
    QObject::connect(dialogHandler, &VKAbstractHandler::sendRequest, this, &VK::processHandler);

    sendNetworkRequest(dialogHandler);
}


void VK::getMessages(int id, bool isChat, int offset) {
    Q_ASSERT(initialized());

    VKHandlerMessages* messagesHandler = new VKHandlerMessages(&storage(), this);
    if (isChat) {
        messagesHandler->setChatId(id);
    } else {
        messagesHandler->setUserId(id);
    }
    messagesHandler->setOffset(offset);
    messagesHandler->setCount(20);
    QObject::connect(messagesHandler, &VKAbstractHandler::ready, this, &VK::sendHandlertoScript);
    QObject::connect(messagesHandler, &VKAbstractHandler::sendRequest, this, &VK::processHandler);

    sendNetworkRequest(messagesHandler);
}

void VK::markAsRead(QList<int> msgs) {
    qDebug()<<msgs;


    VKHandlerMarkAsRead* handler = new VKHandlerMarkAsRead(&storage(), this);

    handler->setMsgs(msgs);
    QObject::connect(handler, &VKAbstractHandler::ready, this, &VK::sendHandlertoScript);
    QObject::connect(handler, &VKAbstractHandler::sendRequest, this, &VK::processHandler);

    sendNetworkRequest(handler);

}

void VK::sendMessage(int userId, bool isChat, QString text, QString forward, QString attachments) {
    auto handler = new VKHandlerSendMessage(&storage(), this);

    handler->setAttachments(attachments);
    handler->setForward(forward);
    handler->setIsChat(isChat);
    handler->setText(text);
    handler->setUserId(userId);
    QObject::connect(handler, &VKAbstractHandler::ready, this, &VK::sendHandlertoScript);
    QObject::connect(handler, &VKAbstractHandler::sendRequest, this, &VK::processHandler);

    sendNetworkRequest(handler);
}


void VK::sendNetworkRequest(VKAbstractHandler *handler) {
    Q_ASSERT(handler);

    QNetworkRequest request = handler->processRequest();
    qDebug()<<request.url().toString();
    QNetworkReply *reply = m_manager->get(request);

    m_networkReplies[reply] = handler;
}

void VK::dropAuthorization() {
    m_VKStorage.setAccessToken("");
    m_VKStorage.setOurUserId(-1);
    delete m_longPoll;
    m_longPoll = new VKLongPollServer(&m_VKStorage, this);
}

void VK::requestFinished(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {

        auto element = m_networkReplies.find(reply);
        if (element != m_networkReplies.end()) {                            //handler
            QString data = reply->readAll();
            qDebug()<<"VK::requestFinished:\n"<<data;
            VKAbstractHandler* handler = element.value();

            QJsonParseError err;
            QJsonDocument document = QJsonDocument::fromJson(data.toUtf8(), &err);
            if (err.error != QJsonParseError::NoError) {
                qFatal("%s",err.errorString().toUtf8().data());
            }
            QJsonObject object = document.object();
            if (object.value("error").type() != QJsonValue::Undefined) {
                errorHandler(object.value("error").toObject(), handler);
            } else {
                if (object.contains("response")) {
                    QJsonValue response = object.value("response");
                    QJsonObject responseObject = response.toObject();
                    
                    QJsonObject longPoll = responseObject.value("longPoll").toObject();
                    if (responseObject.value("longPoll").isObject()) {
                        m_longPoll->init(this, &m_VKStorage,
                                        longPoll.value("key").toString(),
                                        longPoll.value("server").toString(), 
                                        longPoll.value("ts").toInt(),
                                        longPoll.value("pts").toInt());
                    }
                    
                    handler->processReply(&response);

                } else {
                    qCritical()<<"no response";
                }
            }
        } else {
            qCritical()<<"error";
        }
    } else {
        qCritical()<<"Reply error"<<reply->errorString();
        Q_ASSERT(0);
    }
}













void VK::subscribeLongPollServer(QString identification, QString additional, QString key, QString server, int ts) {
    Q_ASSERT(initialized());

    QUrl url(QString("https://%1?act=a_check&key=%2&ts=%3&wait=25&mode=2").arg(server).arg(key).arg(ts));

    qDebug()<<url.toString();

    QNetworkReply* reply = m_manager->get(QNetworkRequest(url));

    m_replies[reply] = QPair<QString,QString>(identification,additional);
}

void VK::getLongPollMessageInformation(QString identification, QString additional, QString userIds, QString fwdMessagesIds) {
    Q_ASSERT(initialized());
    QList<QPair<QString,QString>> args;

    QString execute;
    if (userIds.length() && !fwdMessagesIds.length()) {
        execute = QString("\
return {\"users\":API.users.get({\"user_ids\":\"%1\",\"fields\":\"photo_50\"}),\"fwd\":[]};\
").arg(userIds);
    } else if (!userIds.length() && fwdMessagesIds.length()) {
        execute = QString("\
return {\"users\":[], \"fwd\":API.messages.getById({\"message_ids\":\"%1\",\"preview_length\":16})};\
").arg(fwdMessagesIds);
    } else if (userIds.length() && fwdMessagesIds.length()) {
        execute = QString("\
return {\"users\": API.users.get({\"user_ids\":\"%1\",\"fields\":\"photo_50\"}) ,\"fwd\": API.messages.getById({\"message_ids\":\"%2\",\"preview_length\":16})};\
").arg(userIds).arg(fwdMessagesIds);
    } else {
        Q_ASSERT(false);
    }

    qDebug()<<execute;

    args.push_back({"code", execute.replace("+","%2B")});
                                  sendRequest("execute", args, identification, additional);
                              }


void VK::getLongPollHistory(QString identification, QString additional, int ts, int pts, int messageId) {
    Q_ASSERT(initialized());
    QList<QPair<QString,QString>> args;

    QString execute = QString("\
return API.messages.getLongPollHistory({\"ts\":%1,\"pts\":%2,\"preview_length\":16,\"max_msg_id\":%3});\
").arg(ts).arg(pts).arg(messageId);

    qDebug()<<execute;

    args.push_back({"code", execute.replace("+","%2B")});
    sendRequest("execute", args, identification, additional);
}

void VK::getUserInformation(QString identificator, QString additional, QString ids, QString fields) {
    Q_ASSERT(initialized());

    QList<QPair<QString,QString>> args;

    QString execute = QString("\
return API.users.get({\"user_ids\":\"%1\",\"fields\":\"%2\"});\
").arg(ids).arg(fields);

    qDebug()<<execute;

    args.push_back({"code", execute.replace("+","%2B")});
                       sendRequest("execute", args, identificator, additional);
}


void VK::getFriends(QString identificator, QString additional, int user_id) {
    Q_ASSERT(initialized());

    QList<QPair<QString,QString>> args;

    QString execute = QString("\
return API.friends.get({\"user_id\":%1,\"order\":\"hints\",\"fields\":\"photo_100\"});\
").arg(user_id);

    qDebug()<<execute;

    args.push_back({"code", execute.replace("+","%2B")});
    sendRequest("execute", args, identificator, additional);
}

bool VK::isOurUserAuthorized() {
    return m_VKStorage.isAuthorizred();
}

void VK::sendRequest(QString method, QList<QPair<QString,QString>> args, QString identificator, QString additional) {
    QUrl url(QString("https://api.vk.com/method/%1").arg(method));

    args.push_back({"access_token","123"});

    QUrlQuery query;
    args.push_back({"v","5.28"});
    query.setQueryItems(args);
    url.setQuery(query);

    qDebug()<<url.toString();

    QNetworkReply* reply = m_manager->get(QNetworkRequest(url));

                                                  m_replies[reply] = QPair<QString,QString>(identificator,additional);
                                              }





