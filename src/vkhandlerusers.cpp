#include "vkhandlerusers.h"

VKHandlerUsers::VKHandlerUsers(VKStorage* storage, QObject *parent) :
    VKAbstractHandler(storage, parent)
{
}

const QNetworkRequest VKHandlerUsers::processRequest() {
    qFatal("not implemented");
    return QNetworkRequest();
}
