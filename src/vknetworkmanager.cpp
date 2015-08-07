#include "vknetworkmanager.h"

VKNetworkManager::VKNetworkManager(QObject *parent) :
    QObject(parent)
{
    m_time = QDateTime::currentDateTimeUtc();
    QObject::connect(&m_manager, &QNetworkAccessManager::finished, this, &VKNetworkManager::requestFinished);
}

VKAbstractHandler *VKNetworkManager::getHandlerByReply(QNetworkReply *reply) {
    if (m_networkReplies.contains(reply)) {
        return m_networkReplies[reply];
    }
    Q_ASSERT(0);
    return NULL;
}

void VKNetworkManager::sendRequest(VKAbstractHandler *handler) {

    auto time = QDateTime::currentDateTimeUtc();
    if (m_time < time) {
        send(handler);
        m_time = time.addMSecs(WAIT_TIME_MS);                              //400ms
    } else {
        if (m_data.isEmpty()) {
            QTimer::singleShot(m_time.toMSecsSinceEpoch() - time.toMSecsSinceEpoch(), this, SLOT(timeout()));
        }
        m_time = m_time.addMSecs(WAIT_TIME_MS);
        m_data.push_back({time, handler});
    }

}

void VKNetworkManager::remove(QNetworkReply *reply) {
    m_networkReplies.remove(reply);
}

void VKNetworkManager::send(VKAbstractHandler *handler) {
    QNetworkRequest request = handler->processRequest();
    qDebug()<<request.url().toString();
    QNetworkReply *reply = m_manager.get(request);

    m_networkReplies[reply] = handler;
}

void VKNetworkManager::timeout() {
    auto e = m_data.first(); m_data.removeFirst();

    sendRequest(e.second);

    auto time = QDateTime::currentDateTimeUtc();
    if (m_data.length()) {
        QTimer::singleShot(time.addMSecs(WAIT_TIME_MS).toMSecsSinceEpoch(),this, SLOT(timeout()));
    }
}

void VKNetworkManager::requestFinished(QNetworkReply *reply) {
    emit finished(reply);
}
