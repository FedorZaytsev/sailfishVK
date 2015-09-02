#include "vkcontainervideo.h"

VKContainerVideo::VKContainerVideo(QObject *parent) :
    VKAbstractContainer(parent)
{
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


