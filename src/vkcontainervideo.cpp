#include "vkcontainervideo.h"

VKContainerVideo::VKContainerVideo(QObject *parent) :
    VKAbstractContainer(parent)
{
    m_type = eVKContainerVideo;
}

void VKContainerVideo::setId(int arg) {
    SET_ARG(m_id, arg);
}

void VKContainerVideo::setOwnerId(int arg) {
    SET_ARG(m_ownerId, arg);
}

void VKContainerVideo::setTitle(QString arg) {
    SET_ARG(m_title, arg);
}

void VKContainerVideo::setDescription(QString arg) {
    SET_ARG(m_description, arg);
}

void VKContainerVideo::setDuration(int arg) {
    SET_ARG(m_duration, arg);
}

void VKContainerVideo::setLink(QString arg) {
    SET_ARG(m_link, arg);
}

void VKContainerVideo::setPhoto130(QString arg) {
    SET_ARG(m_photo130, arg);
}

void VKContainerVideo::setPhoto320(QString arg) {
    SET_ARG(m_photo320, arg);
}

void VKContainerVideo::setPhoto640(QString arg) {
    SET_ARG(m_photo640, arg);
}

void VKContainerVideo::setDate(QDateTime arg) {
    SET_ARG(m_date, arg);
}

void VKContainerVideo::setAddingDate(QDateTime arg) {
    SET_ARG(m_addingDate, arg);
}

void VKContainerVideo::setViews(int arg) {
    SET_ARG(m_views, arg);
}

void VKContainerVideo::setComments(int arg) {
    SET_ARG(m_comments, arg);
}

void VKContainerVideo::setPlayerUrl(QString arg) {
    SET_ARG(m_playerUrl, arg);
}

void VKContainerVideo::setIsProcessing(bool arg) {
    SET_ARG(m_isProcessing, arg);
}

void VKContainerVideo::setAccessToken(QString arg) {
    SET_ARG(m_accessToken, arg);
}

void VKContainerVideo::setCanEdit(bool arg) {
    SET_ARG(m_canEdit, arg);
}

QSharedPointer<VKContainerVideo> VKContainerVideo::fromJson(VKStorage *storage, QJsonObject obj, QJsonArray users, QVector<int> userIds) {
    Q_UNUSED(storage);
    Q_UNUSED(users);
    Q_UNUSED(userIds);
    auto video = new VKContainerVideo;

    video->setComments(obj.value("comments").toInt());
    video->setDescription(obj.value("description").toString());
    video->setDuration(obj.value("duration").toInt());
    video->setId(obj.value("id").toInt());
    video->setIsProcessing(obj.value("processing").toInt() == 1);
    video->setLink(obj.value("link").toString());
    video->setOwnerId(obj.value("owner_id").toInt());
    video->setPhoto130(obj.value("photo_130").toString());
    video->setPhoto320(obj.value("photo_320").toString());
    video->setPhoto640(obj.value("photo_640").toString());
    video->setPlayerUrl(obj.value("player").toString());
    video->setTitle(obj.value("title").toString());
    video->setViews(obj.value("views").toInt());
    video->setAccessToken(obj.value("access_toke").toString());
    video->setCanEdit(obj.value("can_edit").toInt() == 1);

    QDateTime date;
    date.setTime_t(obj.value("date").toInt());
    video->setDate(date);
    QDateTime addingDate;
    addingDate.setTime_t(obj.value("adding_date").toInt());
    video->setAddingDate(addingDate);

    return QSharedPointer<VKContainerVideo>(video);
}


