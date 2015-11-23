#ifndef VKCONTAINERSTICKER_H
#define VKCONTAINERSTICKER_H

#include "vkabstractcontainer.h"
#include "vkstorage.h"

class VKContainerSticker : public VKAbstractContainer
{
    Q_OBJECT
public:
    explicit VKContainerSticker(VKStorage *storage, QObject *parent = 0);
    static QSharedPointer<VKContainerSticker> fromJson(VKStorage* storage, QJsonObject obj, const QJsonArray users);

signals:

public slots:

};

#endif // VKCONTAINERSTICKER_H
