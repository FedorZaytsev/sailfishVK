#include "qmlnetworkaccessmanagerfactory.h"

QmlNetworkAccessManagerFactory::QmlNetworkAccessManagerFactory() :
    QQmlNetworkAccessManagerFactory()
{
}

QNetworkAccessManager *QmlNetworkAccessManagerFactory::create(QObject *parent) {
    auto mgr = new QNetworkAccessManager(parent);
    auto cache = new QNetworkDiskCache(mgr);

    cache->setCacheDirectory(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));

    mgr->setCache(cache);

    return mgr;
}
