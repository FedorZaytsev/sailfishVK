#include "vkcontainerwallreply.h"

VKContainerWallReply::VKContainerWallReply(VKStorage *storage, QObject *parent) :
    VKAbstractContainer(storage, parent)
{
    m_type = eVKContainerWallReply;
}

QSharedPointer<VKContainerWallReply> VKContainerWallReply::fromJson(VKStorage *storage, QJsonObject obj, QJsonArray users) {
    Q_UNUSED(storage);
    Q_UNUSED(obj);
    Q_UNUSED(users);

    auto wallReply = QSharedPointer<VKContainerWallReply>(new VKContainerWallReply(storage));
    wallReply->beginObjectChange();

    wallReply->setValid();
    wallReply->endObjectChange();
    return wallReply;
}

