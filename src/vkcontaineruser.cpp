#include "vkcontaineruser.h"

VKContainerUser::VKContainerUser(QObject *parent) :
    VKAbstractContainer(parent)
{
    valid(true);
    setIsOnline(false);
}

VKContainerUser *VKContainerUser::fromJson(VKStorage *storage, const QJsonObject &obj) {
    Q_UNUSED(storage);
    VKContainerUser* user = new VKContainerUser;
    user->setId(obj.value("id").toInt());
    user->setFirstName(obj.value("first_name").toString());
    user->setLastName(obj.value("last_name").toString());
    user->setIconSmall(obj.value("photo_50").toString());
    user->setIconMedium(obj.value("photo_100").toString());
    user->setIconLarge(obj.value("photo_200").toString());
    user->setIsOnline(obj.value("online").toInt() == 1 || obj.value("online_mobile").toInt() == 1);
    return user;
}

VKContainerUser *VKContainerUser::fromSql(VKStorage *storage, QSqlQuery &query) {
    Q_UNUSED(storage);
    VKContainerUser* user = new VKContainerUser;
    user->setId(query.value("id").toInt());
    user->setFirstName(query.value("first_name").toString());
    user->setLastName(query.value("second_name").toString());
    user->setIconSmall(query.value("photo_50").toString());
    user->setIconMedium(query.value("photo_100").toString());
    user->setIconLarge(query.value("photo_200").toString());
    return user;
}

void VKContainerUser::copyTo(VKContainerUser *user) {
    user->setId(id());
    user->setFirstName(firstName());
    user->setLastName(lastName());
    user->setIconSmall(iconSmall());
    user->setIconMedium(iconMedium());
    user->setIconLarge(iconLarge());
}


