#include "vkcontainersticker.h"

VKContainerSticker::VKContainerSticker(VKStorage *storage, QObject *parent) :
    VKAbstractContainer(storage, parent)
{
    m_type = eVKContainerSticker;
}

QSharedPointer<VKContainerSticker> VKContainerSticker::fromJson(VKStorage *storage, QJsonObject obj, QJsonArray users) {
    Q_UNUSED(storage);
    Q_UNUSED(obj);
    Q_UNUSED(users);

    auto sticker = new VKContainerSticker(storage);
    sticker->beginObjectChange();

    sticker->setValid();
    sticker->endObjectChange();
    return QSharedPointer<VKContainerSticker>(sticker);
}
