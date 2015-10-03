#include "vkabstractcontainer.h"
#include "vkabstracthandler.h"

VKAbstractContainer::VKAbstractContainer(QObject *parent) :
    QObject(parent)
{
    //Set ownership to prevent from deleting component from QML engine
    //All containers must be deleted only via sharedpointer
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    m_type = eVKContainerAbstract;
}

void VKAbstractContainer::complete(VKAbstractHandler *h) {
    Q_UNUSED(h);
}

void VKAbstractContainer::copyTo(VKAbstractContainer *container) {
    Q_UNUSED(container);
    Q_ASSERT(0);
}

void VKAbstractContainer::printOwnership()
{
    if (QQmlEngine::objectOwnership(this) == QQmlEngine::CppOwnership) {
        qDebug()<<"cpp";
    } else if (QQmlEngine::objectOwnership(this) == QQmlEngine::JavaScriptOwnership) {
        qDebug()<<"javascript";
    } else {
        qDebug()<<"wtf??";
    }
}
