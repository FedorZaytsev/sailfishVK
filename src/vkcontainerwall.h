#ifndef VKCONTAINERWALL_H
#define VKCONTAINERWALL_H

#include "vkabstractcontainer.h"
#include "vkstorage.h"

class VKContainerWall : public VKAbstractContainer
{
    Q_OBJECT
public:
    explicit VKContainerWall(VKStorage *storage, QObject *parent = 0);
    static QSharedPointer<VKContainerWall> fromJson(VKStorage* storage, QJsonObject obj, const QJsonArray users);

signals:

public slots:

};

#endif // VKCONTAINERWALL_H
