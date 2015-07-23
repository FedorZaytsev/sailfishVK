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
    explicit VKContainerVideo(QObject *parent = 0);
    static VKContainerVideo *fromJson(VKStorage* storage, QJsonObject obj, const QJsonArray users, QVector<int> userIds = QVector<int>());

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


    void setId(int arg)                 { m_id = arg; }
    void setOwnerId(int arg)            { m_ownerId = arg; }
    void setTitle(QString arg)          { m_title = arg; }
    void setDescription(QString arg)    { m_description = arg; }
    void setDuration(int arg)           { m_duration = arg; }
    void setLink(QString arg)           { m_link = arg; }
    void setPhoto130(QString arg)       { m_photo130 = arg; }
    void setPhoto320(QString arg)       { m_photo320 = arg; }
    void setPhoto640(QString arg)       { m_photo640 = arg; }
    void setDate(QDateTime arg)         { m_date = arg; }
    void setAddingDate(QDateTime arg)   { m_addingDate = arg; }
    void setViews(int arg)              { m_views = arg; }
    void setComments(int arg)           { m_comments = arg; }
    void setPlayerUrl(QString arg)      { m_playerUrl = arg; }
    void setIsProcessing(bool arg)      { m_isProcessing = arg; }


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
};

#endif // VKCONTAINERVIDEO_H
