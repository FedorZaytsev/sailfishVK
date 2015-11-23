#ifndef VKCONTAINERVIDEO_H
#define VKCONTAINERVIDEO_H

#include <QJsonArray>
#include <QJsonObject>
#include <QDateTime>
#include "vkabstractcontainer.h"

class VKContainerVideo;
class VKStorage;
class VKContainerVideo : public VKAbstractContainer
{
    Q_OBJECT
public:
    explicit VKContainerVideo(VKStorage *storage, QObject *parent = 0);
    static QSharedPointer<VKContainerVideo> fromJson(VKStorage* storage, QJsonObject obj, const QJsonArray users);

    Q_INVOKABLE int id()                { return m_id; }
    Q_INVOKABLE int ownerId()           { return m_ownerId; }
    Q_INVOKABLE QString title()         { return m_title; }
    Q_INVOKABLE QString description()   { return m_description; }
    Q_INVOKABLE int duration()          { return m_duration; }
    Q_INVOKABLE QString link()          { return m_link; }
    Q_INVOKABLE QString photo130()      { return m_photo130; }
    Q_INVOKABLE QString photo320()      { return m_photo320; }
    Q_INVOKABLE QString photo640()      { return m_photo640; }
    Q_INVOKABLE QDateTime date()        { return m_date; }
    Q_INVOKABLE QDateTime addingDate()  { return m_addingDate; }
    Q_INVOKABLE int views()             { return m_views; }
    Q_INVOKABLE int comments()          { return m_comments; }
    Q_INVOKABLE QString playerUrl()     { return m_playerUrl; }
    Q_INVOKABLE bool isProcessing()     { return m_isProcessing; }
    Q_INVOKABLE QString accessToken()   { return m_accessToken; }
    Q_INVOKABLE bool canEdit()          { return m_canEdit; }


    void setId(int arg);
    void setOwnerId(int arg);
    void setTitle(QString arg);
    void setDescription(QString arg);
    void setDuration(int arg);
    void setLink(QString arg);
    void setPhoto130(QString arg);
    void setPhoto320(QString arg);
    void setPhoto640(QString arg);
    void setDate(QDateTime arg);
    void setAddingDate(QDateTime arg);
    void setViews(int arg);
    void setComments(int arg);
    void setPlayerUrl(QString arg);
    void setIsProcessing(bool arg);
    void setAccessToken(QString arg);
    void setCanEdit(bool arg);


signals:

public slots:
private:
    int m_id;
    int m_ownerId;
    QString m_title;
    QString m_description;
    int m_duration;
    QString m_link;
    QString m_photo130;
    QString m_photo320;
    QString m_photo640;
    QDateTime m_date;
    QDateTime m_addingDate;
    int m_views;
    int m_comments;
    QString m_playerUrl;
    bool m_isProcessing;
    QString m_accessToken;
    bool m_canEdit;
};

#endif // VKCONTAINERVIDEO_H
