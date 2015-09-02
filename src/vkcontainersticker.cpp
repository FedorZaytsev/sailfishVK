#include "vkcontainersticker.h"

VKContainerSticker::VKContainerSticker(QObject *parent) :
    VKAbstractContainer(parent)
{
}

QSharedPointer<VKContainerSticker> VKContainerSticker::fromJson(VKStorage *storage, QJsonObject obj, QJsonArray users, QVector<int> userIds) {
    Q_UNUSED(storage);
    Q_UNUSED(obj);
    Q_UNUSED(users);
    Q_UNUSED(userIds);

    auto sticker = new VKContainerSticker;


    return QSharedPointer<VKContainerSticker>(sticker);
}
