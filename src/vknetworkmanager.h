#ifndef VKNETWORKMANAGER_H
#define VKNETWORKMANAGER_H

#include <QPair>
#include <QTimer>
#include <QObject>
#include <QDateTime>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include "vkabstracthandler.h"

#define WAIT_TIME_MS 500

class VKNetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit VKNetworkManager(QObject *parent = 0);

    VKAbstractHandler* getHandlerByReply(QNetworkReply* reply);
    void sendRequest(VKAbstractHandler* handler);
    void remove(QNetworkReply* reply);
private:
    void send(VKAbstractHandler* handler);
signals:
    void finished(QNetworkReply* reply);
public slots:
    void timeout();
    void requestFinished(QNetworkReply* reply);
private:
    QNetworkAccessManager m_manager;
    QMap<QNetworkReply*, VKAbstractHandler*> m_networkReplies;
    QVector<QPair<QDateTime, VKAbstractHandler*>> m_data;
    QDateTime m_time;
};

#endif // VKNETWORKMANAGER_H
