#include "vkcontainerlink.h"

VKContainerLink::VKContainerLink(VKStorage *storage, QObject *parent) :
    VKAbstractContainer(storage, parent)
{
    m_type = eVKContainerLink;
}

QSharedPointer<VKContainerLink> VKContainerLink::fromJson(VKStorage *storage, QJsonObject obj, QJsonArray users) {
    Q_UNUSED(storage);
    Q_UNUSED(users);

    auto link = QSharedPointer<VKContainerLink>(new VKContainerLink(storage));
    link->beginObjectChange();

    link->setDescription(obj.value("description").toString());
    link->setTitle(obj.value("title").toString());
    link->setUrl(obj.value("url").toString());

    link->setValid();
    link->endObjectChange();
    return link;
}


void VKContainerLink::setUrl(QString arg) {
    SET_ARG(m_url, arg);
}

void VKContainerLink::setTitle(QString arg) {
    SET_ARG(m_title, arg);
}

void VKContainerLink::setDescription(QString arg) {
    SET_ARG(m_description, arg);
}
