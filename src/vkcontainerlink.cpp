#include "vkcontainerlink.h"

VKContainerLink::VKContainerLink(QObject *parent) :
    VKAbstractContainer(parent)
{
}

VKContainerLink *VKContainerLink::fromJson(VKStorage *storage, QJsonObject obj, QJsonArray users, QVector<int> userIds) {
    Q_UNUSED(storage);
    Q_UNUSED(users);
    Q_UNUSED(userIds);

    auto link = new VKContainerLink;
    link->setDescription(obj.value("description").toString());
    link->setTitle(obj.value("title").toString());
    link->setUrl(obj.value("url").toString());

    return link;
}
