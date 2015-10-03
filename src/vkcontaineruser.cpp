#include "vkcontaineruser.h"

VKContainerUser::VKContainerUser(QObject *parent) :
    VKAbstractContainer(parent)
{
    valid(true);
    setIsOnline(false);
    m_type = eVKContainerUser;
}

VKContainerUser::~VKContainerUser() {
}

QSharedPointer<VKContainerUser> VKContainerUser::fromJson(VKStorage *storage, const QJsonObject &obj) {
    Q_UNUSED(storage);
    auto user = QSharedPointer<VKContainerUser>(new VKContainerUser);
    user->setId(obj.value("id").toInt());
    user->setFirstName(obj.value("first_name").toString());
    user->setLastName(obj.value("last_name").toString());
    user->setIconSmall(obj.value("photo_50").toString());
    user->setIconMedium(obj.value("photo_100").toString());
    user->setIconLarge(obj.value("photo_200").toString());
    user->setIsOnline(obj.value("online").toInt() == 1 || obj.value("online_mobile").toInt() == 1);
    return user;
}

QString VKContainerUser::userName() const {
    return firstName() + " " + lastName();
}

void VKContainerUser::setId(int arg) {
    SET_ARG(m_id, arg);
}

void VKContainerUser::setFirstName(QString arg) {
    SET_ARG(m_firstName, arg);
}

void VKContainerUser::setLastName(QString arg) {
    SET_ARG(m_lastName, arg);
}

void VKContainerUser::setIconSmall(QString arg) {
    SET_ARG(m_iconSmall, arg);
}

void VKContainerUser::setIconMedium(QString arg) {
    SET_ARG(m_iconMedium, arg);
}

void VKContainerUser::setIconLarge(QString arg) {
    SET_ARG(m_iconLarge, arg);
}

void VKContainerUser::setIsOnline(bool arg) {
    SET_ARG(m_online, arg);
}


