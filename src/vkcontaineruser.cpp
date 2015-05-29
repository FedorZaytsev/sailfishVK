#include "vkcontaineruser.h"

VKContainerUser::VKContainerUser(QObject *parent) :
    VKAbstractContainer(parent)
{
}

VKContainerUser *VKContainerUser::fromJson(VKStorage *storage, QJsonObject &obj) {
    VKContainerUser* user = new VKContainerUser;
    user->setId(obj.value("id").toInt());
    user->setFirstName(obj.value("first_name").toString());
    user->setLastName(obj.value("last_name").toString());
    user->setIconSmall(obj.value("photo_50").toString());
    user->setIconMedium(obj.value("photo_100").toString());
    user->setIconLarge(obj.value("photo_200").toString());
    storage->addUser(user);
    return user;
}

VKContainerUser *VKContainerUser::fromSql(VKStorage *storage, QSqlQuery &query) {
    VKContainerUser* user = new VKContainerUser;
    user->setId(query.value("id").toInt());
    user->setFirstName(query.value("first_name").toString());
    user->setLastName(query.value("second_name").toString());
    user->setIconSmall(query.value("photo_50").toString());
    user->setIconMedium(query.value("photo_100").toString());
    user->setIconLarge(query.value("photo_200").toString());
    return user;
}


