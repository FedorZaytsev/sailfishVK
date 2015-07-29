#include "vkcontainerphoto.h"

VKContainerPhoto::VKContainerPhoto(QObject *parent) :
    VKAbstractContainer(parent)
{
}

VKContainerPhoto *VKContainerPhoto::fromJson(VKStorage *storage, QJsonObject obj, QJsonArray users, QVector<int> userIds) {
    Q_UNUSED(storage);
    Q_UNUSED(users);
    Q_UNUSED(userIds);
    VKContainerPhoto* photo = new VKContainerPhoto;

    photo->setAlbumId(obj.value("album_id").toInt());
    photo->setHeight(obj.value("height").toInt());
    photo->setId(obj.value("id").toInt());
    photo->setOwnerId(obj.value("owner_id").toInt());
    photo->setPhoto75(obj.value("photo_75").toString());
    photo->setPhoto130(obj.value("photo_130").toString());
    photo->setPhoto604(obj.value("photo_604").toString());
    photo->setPhoto807(obj.value("photo_807").toString());
    photo->setPhoto1280(obj.value("photo_1280").toString());
    photo->setPhoto2560(obj.value("photo_2560").toString());
    photo->setUserId(obj.value("user_id").toInt());
    photo->setWidth(obj.value("width").toInt());

    QDateTime date;
    date.setTime_t(obj.value("date").toInt());
    return photo;
}

QString VKContainerPhoto::maxSuitablePhoto() {
    if (photo604().length()) {
        return photo604();
    } else if (photo130().length()) {
        return photo130();
    } else if (photo75().length()) {
        return photo75();
    }
    Q_ASSERT(0);
    return "";
}

QSize VKContainerPhoto::maxSuitableSize() {
    if (photo604().length()) {
        return calculatePhotoSize({604, 604});
    } else if (photo130().length()) {
        return calculatePhotoSize({130, 130});
    } else if (photo75().length()) {
        return calculatePhotoSize({75, 75});
    }
    Q_ASSERT(0);
    return QSize();
}

QSize VKContainerPhoto::calculatePhotoSize(QSize size) {
    float coefWidth = size.width()/m_width;
    float coefHeight = size.height()/m_height;

    float max = qMax(coefWidth, coefHeight);

    if (max > 1.0) {
        return size*max;
    }

    return size;

}
