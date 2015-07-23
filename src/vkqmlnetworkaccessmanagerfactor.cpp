#include "vkqmlnetworkaccessmanagerfactor.h"

VKQmlNetworkAccessManagerFactor::VKQmlNetworkAccessManagerFactor()
{
}

QNetworkAccessManager *VKQmlNetworkAccessManagerFactor::create(QObject *parent) {
    Q_UNUSED(parent);
    return NULL;
}
