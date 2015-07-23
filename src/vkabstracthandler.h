#ifndef ABSTRACTVKHANDLER_H
#define ABSTRACTVKHANDLER_H

#include <QObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QUrlQuery>
#include "vkstorage.h"
#include "vkabstractcontainer.h"

#define DEFAULT_PREVIEW_LENGTH 16
#define DEFAULT_COUNT 20

class VKAbstractHandler;

class VKAbstractHandler : public QObject
{
    Q_OBJECT
public:
    explicit VKAbstractHandler(VKStorage* storage, QObject *parent = 0);
    virtual const QNetworkRequest processRequest() = 0;
    virtual void processReply(QJsonValue*) = 0;
    virtual QString name() = 0;
            QJsonValue data();
protected:
    const QNetworkRequest generateRequest(QString method, QList<QPair<QString,QString>>& args);
signals:
    void ready(VKAbstractHandler*);
    void sendRequest(VKAbstractHandler* handler);
public slots:
protected:
    VKStorage* storage() const;
    QJsonValue m_data;
    VKStorage* m_storage;
private:
};

#endif // ABSTRACTVKHANDLER_H
