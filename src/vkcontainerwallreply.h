#ifndef VKCONTAINERWALLREPLY_H
#define VKCONTAINERWALLREPLY_H

#include "vkabstractcontainer.h"
#include "vkstorage.h"

class VKContainerWallReply : public VKAbstractContainer
{
    Q_OBJECT
public:
    explicit VKContainerWallReply(VKStorage *storage, QObject *parent = 0);
    static QSharedPointer<VKContainerWallReply> fromJson(VKStorage* storage, QJsonObject obj, const QJsonArray users);

signals:

public slots:

};

#endif // VKCONTAINERWALLREPLY_H
