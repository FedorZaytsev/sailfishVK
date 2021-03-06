#include "vkcontainerdocument.h"

VKContainerDocument::VKContainerDocument(VKStorage *storage, QObject *parent) :
    VKAbstractContainer(storage, parent)
{
    m_type = eVKContainerDocument;
}

QSharedPointer<VKContainerDocument> VKContainerDocument::fromJson(VKStorage *storage, QJsonObject obj, QJsonArray users) {
    Q_UNUSED(storage);
    Q_UNUSED(users);

    auto doc = QSharedPointer<VKContainerDocument>(new VKContainerDocument(storage));
    doc->beginObjectChange();

    doc->setExt(obj.value("ext").toString());
    doc->setId(obj.value("id").toInt());
    doc->setOwnerId(obj.value("owner_id").toInt());
    doc->setPhoto100(obj.value("photo_100").toString());
    doc->setPhoto130(obj.value("photo_130").toString());
    doc->setSize(obj.value("size").toInt());
    doc->setTitle(obj.value("title").toString());
    doc->setUrl(obj.value("url").toString());

    doc->setValid();
    doc->endObjectChange();
    return doc;
}


void VKContainerDocument::setId(int arg) {
    SET_ARG(m_id, arg);
}

void VKContainerDocument::setOwnerId(int arg) {
    SET_ARG(m_ownerId, arg);
}

void VKContainerDocument::setTitle(QString arg) {
    SET_ARG(m_title, arg);
}

void VKContainerDocument::setSize(int arg) {
    SET_ARG(m_size, arg);
}

void VKContainerDocument::setExt(QString arg) {
    SET_ARG(m_ext, arg);
}

void VKContainerDocument::setUrl(QString arg) {
    SET_ARG(m_url, arg);
}

void VKContainerDocument::setPhoto100(QString arg) {
    SET_ARG(m_photo100, arg);
}

void VKContainerDocument::setPhoto130(QString arg) {
    SET_ARG(m_photo130, arg);
}
