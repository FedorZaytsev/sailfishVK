#include "vkcontaineraudio.h"

VKContainerAudio::VKContainerAudio(VKStorage *storage, QObject *parent) :
    VKAbstractContainer(storage, parent)
{
    m_type = eVKContainerAudio;
}

QSharedPointer<VKContainerAudio> VKContainerAudio::fromJson(VKStorage *storage, QJsonObject obj, QJsonArray users) {
    Q_UNUSED(storage);
    Q_UNUSED(users);
    auto audio = new VKContainerAudio(storage);
    audio->beginObjectChange();

    audio->setAlbum(obj.value("album").toInt());
    audio->setArtist(obj.value("artist").toString());
    audio->setDuration(obj.value("duration").toInt());
    audio->setGenre(obj.value("genre_id").toInt());
    audio->setId(obj.value("id").toInt());
    audio->setLyrics(obj.value("lyrics_id").toInt());
    audio->setOwnerId(obj.value("owner_id").toInt());
    audio->setTitle(obj.value("title").toString());
    audio->setUrl(obj.value("url").toString());

    audio->setValid();
    audio->endObjectChange();
    return QSharedPointer<VKContainerAudio>(audio);
}


void VKContainerAudio::setId(int arg) {
    SET_ARG(m_id, arg);
}

void VKContainerAudio::setOwnerId(int arg) {
    SET_ARG(m_ownerId, arg);
}

void VKContainerAudio::setArtist(QString arg) {
    SET_ARG(m_artist, arg);
}

void VKContainerAudio::setTitle(QString arg) {
    SET_ARG(m_title, arg);
}

void VKContainerAudio::setDuration(int arg) {
    SET_ARG(m_duration, arg);
}

void VKContainerAudio::setUrl(QString arg) {
    SET_ARG(m_url, arg);
}

void VKContainerAudio::setLyrics(int arg) {
    SET_ARG(m_lyricsId, arg);
}

void VKContainerAudio::setAlbum(int arg) {
    SET_ARG(m_albumId, arg);
}

void VKContainerAudio::setGenre(int arg) {
    SET_ARG(m_genreId, arg);
}
