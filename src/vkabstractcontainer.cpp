#include "vkabstractcontainer.h"
#include "vkcontainermessage.h"
#include "vkabstracthandler.h"

VKAbstractContainer::VKAbstractContainer(VKStorage *storage, QObject *parent) :
    IVKCompletable(parent)
{
    //Set ownership to prevent from deleting component from QML engine
    //All containers must be deleted only via sharedpointer
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    m_type = eVKContainerAbstract;
    m_storage = storage;
    m_valid = false;
}

void VKAbstractContainer::complete(QSharedPointer<VKContainerUser> c) {
    Q_UNUSED(c);
}

void VKAbstractContainer::copyTo(VKAbstractContainer *container) {
    Q_UNUSED(container);
    Q_ASSERT(0);
}

int VKAbstractContainer::type() const {
    return m_type;
}

void VKAbstractContainer::beginObjectChange() {

}

void VKAbstractContainer::endObjectChange() {

}

void VKAbstractContainer::emitChange() {
    emit dataChanged(this);
}

VKStorage *VKAbstractContainer::storage() const {
    return m_storage;
}

bool VKAbstractContainer::isValid() const {
    return m_valid;
}

void VKAbstractContainer::setValid() {
    m_valid = true;
}

void VKAbstractContainer::setInvalid() {
    m_valid = false;
}

void VKAbstractContainer::setValid(bool b) {
    m_valid = b;
}

void VKAbstractContainer::printOwnership() {
    if (QQmlEngine::objectOwnership(this) == QQmlEngine::CppOwnership) {
        qDebug()<<"cpp";
    } else if (QQmlEngine::objectOwnership(this) == QQmlEngine::JavaScriptOwnership) {
        qDebug()<<"javascript";
    } else {
        qDebug()<<"wtf??";
    }
}
