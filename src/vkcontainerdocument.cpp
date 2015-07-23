#include "vkcontainerdocument.h"

VKContainerDocument::VKContainerDocument(QObject *parent) :
    VKAbstractContainer(parent)
{
}

VKContainerDocument *VKContainerDocument::fromJson(VKStorage *storage, QJsonObject obj, QJsonArray users, QVector<int> userIds) {
    Q_UNUSED(storage);
    Q_UNUSED(users);
    Q_UNUSED(userIds);
    auto doc = new VKContainerDocument;

    doc->setExt(obj.value("ext").toString());
    doc->setId(obj.value("id").toInt());
    doc->setOwnerId(obj.value("owner_id").toInt());
    doc->setPhoto100(obj.value("photo_100").toString());
    doc->setPhoto130(obj.value("photo_130").toString());
    doc->setSize(obj.value("size").toInt());
    doc->setTitle(obj.value("title").toString());
    doc->setUrl(obj.value("url").toString());

    return doc;
}