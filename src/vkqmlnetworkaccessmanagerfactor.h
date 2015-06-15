#ifndef VKQMLNETWORKACCESSMANAGERFACTOR_H
#define VKQMLNETWORKACCESSMANAGERFACTOR_H

#include <QNetworkAccessManager>
#include <QQmlNetworkAccessManagerFactory>

class VKQmlNetworkAccessManagerFactor : public QQmlNetworkAccessManagerFactory
{
public:
    VKQmlNetworkAccessManagerFactor();
    virtual QNetworkAccessManager* create(QObject* parent) = 0;
};

#endif // VKQMLNETWORKACCESSMANAGERFACTOR_H
