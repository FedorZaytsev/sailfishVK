#include "vkcontainerwall.h"

VKContainerWall::VKContainerWall(VKStorage *storage, QObject *parent) :
    VKAbstractContainer(storage, parent)
{
    m_type = eVKContainerWall;
}

QSharedPointer<VKContainerWall> VKContainerWall::fromJson(VKStorage *storage, QJsonObject obj, QJsonArray users) {
    Q_UNUSED(storage);
    Q_UNUSED(obj);
    Q_UNUSED(users);

    auto wall = QSharedPointer<VKContainerWall>(new VKContainerWall(storage));
    wall->beginObjectChange();

    wall->setValid();
    wall->endObjectChange();
    return wall;
}
