#include "vkcontaineruser.h"

VKContainerUser::VKContainerUser(VKStorage *storage, QObject *parent) :
    VKAbstractContainer(storage, parent)
{
    beginObjectChange();
    setIsOnline(false);
    endObjectChange();
    m_type = eVKContainerUser;
}

VKContainerUser::~VKContainerUser() {
}

void VKContainerUser::completed() {
    Q_ASSERT(0);
}

QSharedPointer<VKContainerUser> VKContainerUser::fromJson(VKStorage *storage, const QJsonObject &obj) {
    Q_UNUSED(storage);
    auto user = QSharedPointer<VKContainerUser>(new VKContainerUser(storage));
    user->beginObjectChange();

    user->setId(obj.value("id").toInt());
    user->setFirstName(obj.value("first_name").toString());
    user->setLastName(obj.value("last_name").toString());
    user->setIconSmall(obj.value("photo_50").toString());
    user->setIconMedium(obj.value("photo_100").toString());
    user->setIconLarge(obj.value("photo_200").toString());
    user->setIsOnline(obj.value("online").toInt() == 1 || obj.value("online_mobile").toInt() == 1);

    user->setValid();
    user->endObjectChange();
    return user;
}

void VKContainerUser::updateFrom(QSharedPointer<VKContainerUser> user) {
    Q_ASSERT(id() == user->id());
    bool updated = false;

    UPDATE_ARG_CHECK(user,  firstName,  setFirstName,   updated);
    UPDATE_ARG_CHECK(user,  lastName,   setLastName,    updated);
    UPDATE_ARG_CHECK(user,  iconSmall,  setIconSmall,   updated);
    UPDATE_ARG_CHECK(user,  iconMedium, setIconMedium,  updated);
    UPDATE_ARG_CHECK(user,  iconLarge,  setIconLarge,   updated);
    UPDATE_ARG_CHECK(user,  isOnline,   setIsOnline,    updated);

    if (updated) {
        emitChange();
    }

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


