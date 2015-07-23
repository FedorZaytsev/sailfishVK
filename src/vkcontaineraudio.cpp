#include "vkcontaineraudio.h"

VKContainerAudio::VKContainerAudio(QObject *parent) :
    VKAbstractContainer(parent)
{
}

VKContainerAudio *VKContainerAudio::fromJson(VKStorage *storage, QJsonObject obj, QJsonArray users, QVector<int> userIds) {
    Q_UNUSED(storage);
    Q_UNUSED(users);
    Q_UNUSED(userIds);
    auto audio = new VKContainerAudio;

    audio->setAlbum(obj.value("album").toInt());
    audio->setArtist(obj.value("artist").toString());
    audio->setDuration(obj.value("duration").toInt());
    audio->setGenre(obj.value("genre_id").toInt());
    audio->setId(obj.value("id").toInt());
    audio->setLyrics(obj.value("lyrics_id").toInt());
    audio->setOwnerId(obj.value("owner_id").toInt());
    audio->setTitle(obj.value("title").toString());
    audio->setUrl(obj.value("url").toString());

    return audio;
}
