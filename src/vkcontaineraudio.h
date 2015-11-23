#ifndef VKCONTAINERAUDIO_H
#define VKCONTAINERAUDIO_H

#include "vkabstractcontainer.h"

class VKContainerAudio;
class VKContainerAudio : public VKAbstractContainer
{
    Q_OBJECT
public:
    explicit VKContainerAudio(VKStorage *storage, QObject *parent = 0);
    static QSharedPointer<VKContainerAudio> fromJson(VKStorage* storage, QJsonObject obj, const QJsonArray users);

    Q_INVOKABLE int         id()            { return m_id; }
    Q_INVOKABLE int         ownerId()       { return m_ownerId; }
    Q_INVOKABLE QString     artist()        { return m_artist; }
    Q_INVOKABLE QString     title()         { return m_title; }
    Q_INVOKABLE int         duration()      { return m_duration; }
    Q_INVOKABLE QString     url()           { return m_url; }
    Q_INVOKABLE int         lyrics()        { return m_lyricsId; }
    Q_INVOKABLE int         album()         { return m_albumId; }
    Q_INVOKABLE int         genre()         { return m_genreId; }

    void setId(int arg);
    void setOwnerId(int arg);
    void setArtist(QString arg);
    void setTitle(QString arg);
    void setDuration(int arg);
    void setUrl(QString arg);
    void setLyrics(int arg);
    void setAlbum(int arg);
    void setGenre(int arg);

signals:

public slots:
private:
    int m_id;
    int m_ownerId;
    QString m_artist;
    QString m_title;
    int m_duration;
    QString m_url;
    int m_lyricsId;
    int m_albumId;
    int m_genreId;
};

#endif // VKCONTAINERAUDIO_H
