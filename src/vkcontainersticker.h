#ifndef VKCONTAINERSTICKER_H
#define VKCONTAINERSTICKER_H

#include "vkabstractcontainer.h"
#include "vkstorage.h"

class VKContainerSticker : public VKAbstractContainer
{
    Q_OBJECT
public:
    explicit VKContainerSticker(QObject *parent = 0);
    static VKContainerSticker *fromJson(VKStorage* storage, QJsonObject obj, const QJsonArray users, QVector<int> userIds = QVector<int>());

signals:

public slots:

};

#endif // VKCONTAINERSTICKER_H
