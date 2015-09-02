#include "vkabstractcontainer.h"
#include "vkabstracthandler.h"

VKAbstractContainer::VKAbstractContainer(QObject *parent) :
    QObject(parent)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

void VKAbstractContainer::complete(VKAbstractHandler *h) {
    Q_UNUSED(h);
}

void VKAbstractContainer::copyTo(VKAbstractContainer *container) {
    Q_UNUSED(container);
    Q_ASSERT(0);
}

