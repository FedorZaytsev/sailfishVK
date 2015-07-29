#ifndef VKCONTAINERWALLREPLY_H
#define VKCONTAINERWALLREPLY_H

#include "vkabstractcontainer.h"
#include "vkstorage.h"

class VKContainerWallReply : public VKAbstractContainer
{
    Q_OBJECT
public:
    explicit VKContainerWallReply(QObject *parent = 0);
    static VKContainerWallReply *fromJson(VKStorage* storage, QJsonObject obj, const QJsonArray users, QVector<int> userIds = QVector<int>());

signals:

public slots:

};

#endif // VKCONTAINERWALLREPLY_H
