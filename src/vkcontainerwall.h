#ifndef VKCONTAINERWALL_H
#define VKCONTAINERWALL_H

#include "vkabstractcontainer.h"
#include "vkstorage.h"

class VKContainerWall : public VKAbstractContainer
{
    Q_OBJECT
public:
    explicit VKContainerWall(QObject *parent = 0);
    static VKContainerWall *fromJson(VKStorage* storage, QJsonObject obj, const QJsonArray users, QVector<int> userIds = QVector<int>());

signals:

public slots:

};

#endif // VKCONTAINERWALL_H
