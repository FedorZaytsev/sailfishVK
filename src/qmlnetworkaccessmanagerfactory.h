#ifndef QMLNETWORKACCESSMANAGERFACTORY_H
#define QMLNETWORKACCESSMANAGERFACTORY_H

#include <QQmlNetworkAccessManagerFactory>
#include <QNetworkAccessManager>
#include <QNetworkDiskCache>
#include <QStandardPaths>
#include <QCoreApplication>
#include <QDir>

class QmlNetworkAccessManagerFactory : public QQmlNetworkAccessManagerFactory
{
public:
    explicit QmlNetworkAccessManagerFactory();
    virtual QNetworkAccessManager *	create(QObject * parent);
signals:

public slots:

};

#endif // QMLNETWORKACCESSMANAGERFACTORY_H
