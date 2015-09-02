#include "vkcontaineraudio.h"

VKContainerAudio::VKContainerAudio(QObject *parent) :
    VKAbstractContainer(parent)
{
}

QSharedPointer<VKContainerAudio> VKContainerAudio::fromJson(VKStorage *storage, QJsonObject obj, QJsonArray users) {
    Q_UNUSED(storage);
    Q_UNUSED(users);
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

    return QSharedPointer<VKContainerAudio>(audio);
}
