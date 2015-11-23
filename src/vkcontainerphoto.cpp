#include "vkcontainerphoto.h"

VKContainerPhoto::VKContainerPhoto(VKStorage *storage, QObject *parent) :
    VKAbstractContainer(storage, parent)
{
    m_type = eVKContainerPhoto;
}

QSharedPointer<VKContainerPhoto> VKContainerPhoto::fromJson(VKStorage *storage, QJsonObject obj, QJsonArray users) {
    Q_UNUSED(storage);
    Q_UNUSED(users);
    auto photo = QSharedPointer<VKContainerPhoto>(new VKContainerPhoto(storage));
    photo->beginObjectChange();

    photo->setAlbumId(obj.value("album_id").toInt());
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
    photo->setHeight(obj.value("height").toInt());

    QDateTime date;
    date.setTime_t(obj.value("date").toInt());
    photo->setDate(date);

    photo->setValid();
    photo->endObjectChange();
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

void VKContainerPhoto::setId(int id) {
    SET_ARG(m_id, id);
}

void VKContainerPhoto::setAlbumId(int id) {
    SET_ARG(m_albumId, id);
}

void VKContainerPhoto::setOwnerId(int id) {
    SET_ARG(m_ownerId, id);
}

void VKContainerPhoto::setUserId(int id) {
    SET_ARG(m_userId, id);
}

void VKContainerPhoto::setPhoto75(QString photo) {
    SET_ARG(m_photo75, photo);
}

void VKContainerPhoto::setPhoto130(QString photo) {
    SET_ARG(m_photo130, photo);
}

void VKContainerPhoto::setPhoto604(QString photo) {
    SET_ARG(m_photo604, photo);
}

void VKContainerPhoto::setPhoto807(QString photo) {
    SET_ARG(m_photo807, photo);
}

void VKContainerPhoto::setPhoto1280(QString photo) {
    SET_ARG(m_photo1280, photo);
}

void VKContainerPhoto::setPhoto2560(QString photo) {
    SET_ARG(m_photo2560, photo);
}

void VKContainerPhoto::setWidth(int width) {
    SET_ARG(m_width, width);
}

void VKContainerPhoto::setHeight(int height) {
    SET_ARG(m_height, height);
}

void VKContainerPhoto::setDate(QDateTime date) {
    SET_ARG(m_date, date);
}

void VKContainerPhoto::setText(QString text) {
    SET_ARG(m_text, text);
}

QSize VKContainerPhoto::calculatePhotoSize(QSize requiredSize) {
    QSize size(m_width, m_height);
    float coefWidth = requiredSize.width()/size.width();
    float coefHeight = requiredSize.height()/size.height();

    float max = qMax(coefWidth, coefHeight);

    if (max > 1.0) {
        return size*max;
    }

    return size;

}
