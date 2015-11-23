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

    qDebug()<<"adding handler in network manager";
    auto time = QDateTime::currentDateTimeUtc();
    if (!isBusy()) {
        qDebug()<<"direct send";
        send(handler);
        m_time = time.addMSecs(WAIT_TIME_MS);                              //400ms
    } else {
        if (m_data.isEmpty()) {
            qDebug()<<"m_data is empty, setting timer for time"<<(m_time.toMSecsSinceEpoch() - time.toMSecsSinceEpoch());
            QTimer::singleShot(m_time.toMSecsSinceEpoch() - time.toMSecsSinceEpoch(), this, SLOT(timeout()));
        }
        m_time = m_time.addMSecs(WAIT_TIME_MS);
        m_data.push_back({time, handler});
    }

}

void VKNetworkManager::remove(QNetworkReply *reply) {
    m_networkReplies.remove(reply);
}

bool VKNetworkManager::isBusy() {
    return m_time > QDateTime::currentDateTimeUtc();
}

void VKNetworkManager::send(VKAbstractHandler *handler) {
    qDebug()<<QTime::currentTime().toString("mm.ss.zzz");
    QNetworkRequest request = handler->processRequest();
    qDebug()<<QUrl::fromPercentEncoding(request.url().toString().toLatin1());
    QNetworkReply *reply = m_manager.get(request);

    m_networkReplies[reply] = handler;
}

void VKNetworkManager::timeout() {
    qDebug()<<"send event";
    auto e = m_data.first(); m_data.removeFirst();

    send(e.second);

    auto time = QDateTime::currentDateTimeUtc();
    if (m_data.length()) {
        QTimer::singleShot(WAIT_TIME_MS,this, SLOT(timeout()));
    }
}

void VKNetworkManager::requestFinished(QNetworkReply *reply) {
    emit finished(reply);
}
