#include "vkcontainerlink.h"

VKContainerLink::VKContainerLink(QObject *parent) :
    VKAbstractContainer(parent)
{
    m_type = eVKContainerLink;
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

QSharedPointer<VKContainerLink> VKContainerLink::fromJson(VKStorage *storage, QJsonObject obj, QJsonArray users, QVector<int> userIds) {
    Q_UNUSED(storage);
    Q_UNUSED(users);
    Q_UNUSED(userIds);

    auto link = new VKContainerLink;
    link->setDescription(obj.value("description").toString());
    link->setTitle(obj.value("title").toString());
    link->setUrl(obj.value("url").toString());

    return QSharedPointer<VKContainerLink>(link);
}
