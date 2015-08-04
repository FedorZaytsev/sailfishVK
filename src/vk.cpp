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
    m_debugLogBuffer = new DebugLogBuffer(this);

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
    m_isOnline = true;
}

VK::~VK() {}

void VK::storageError(QString msg) {
    qDebug()<<"Storage error"<<msg;
    Q_ASSERT(0);
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

void VK::sendContainersToScript(VKAbstractHandler* handler) {
    qDebug()<<"sendContainersToScript";
    emit handlerReady(handler->name(),  handler);
}

void VK::addDebugLogLine(const QString &line) {
    m_debugLogBuffer->add(line);
}

QString VK::generateBugReport() {
    QString test = QString("-----------ATTENTION!---------\n"
            "Logs can contains some personal information, "
            "such as messages and account details. "
            "Logs do not contains your login/password.\n\n\n"+
            m_debugLogBuffer->generate()).toHtmlEscaped();
    qDebug()<<test;
    return test;
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
    VKHandlerDialogs* dialogHandler = new VKHandlerDialogs(&storage(), this);
    dialogHandler->setOffset(offset);
    dialogHandler->setLongPoll(!m_longPoll->initilized());
    QObject::connect(dialogHandler, &VKAbstractHandler::ready, this, &VK::sendHandlertoScript);
    QObject::connect(dialogHandler, &VKAbstractHandler::sendRequest, this, &VK::processHandler);
    QObject::connect(dialogHandler, &VKHandlerDialogs::unreadCountChanged, [this](int count) {
        emit this->unreadCountChanged(count);
    });

    sendNetworkRequest(dialogHandler);
}


void VK::getMessages(int id, bool isChat, int offset) {
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

bool VK::isOurUserAuthorized() {
    return m_VKStorage.isAuthorizred();
}


void VK::requestFinished(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {

        m_isOnline = true;
        auto element = m_networkReplies.find(reply);
        if (element != m_networkReplies.end()) {
            QString data = reply->readAll();
            qDebug()<<"VK::requestFinished:\n"<<data;
            VKAbstractHandler* handler = element.value();

            QJsonParseError err;
            QJsonDocument document = QJsonDocument::fromJson(data.toUtf8(), &err);
            if (err.error != QJsonParseError::NoError) {
                qFatal("%s",err.errorString().toUtf8().data());
                Q_ASSERT(0);
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
                    Q_ASSERT(0);
                }
            }
        } else {
            qCritical()<<"error";
            Q_ASSERT(0);
        }
    } else {
        qCritical()<<"Reply error"<<reply->errorString();
        if (m_isOnline) {
            displayError("Connection error", ERROR_HANDLER_INFORM);
        }
        auto element = m_networkReplies.find(reply);
        if (element != m_networkReplies.end()) {
            qDebug()<<"Network error, trying to reconnect";

            m_networkReplies.remove(reply);
            sendNetworkRequest(element.value());

        }
        m_isOnline = false;
    }
}


