#ifndef VKCONTAINERPHOTO_H
#define VKCONTAINERPHOTO_H

#include <QJsonArray>
#include <QJsonObject>
#include <QDateTime>
#include <QSize>
#include "vkabstractcontainer.h"

class VKStorage;
class VKContainerPhoto : public VKAbstractContainer
{
    Q_OBJECT
public:
    explicit VKContainerPhoto(QObject *parent = 0);
    static QSharedPointer<VKContainerPhoto> fromJson(VKStorage* storage, QJsonObject obj, const QJsonArray users, QVector<int> userIds = QVector<int>());

    Q_INVOKABLE int         id()            { return m_id; }
    Q_INVOKABLE int         albumId()       { return m_albumId; }
    Q_INVOKABLE int         ownerId()       { return m_ownerId; }
    Q_INVOKABLE int         userId()        { return m_userId; }
    Q_INVOKABLE QString     photo75()       { return m_photo75; }
    Q_INVOKABLE QString     photo130()      { return m_photo130; }
    Q_INVOKABLE QString     photo604()      { return m_photo604; }
    Q_INVOKABLE QString     photo807()      { return m_photo807; }
    Q_INVOKABLE QString     photo1280()     { return m_photo1280; }
    Q_INVOKABLE QString     photo2560()     { return m_photo2560; }
    Q_INVOKABLE QSize       size()          { return QSize(m_width, m_height); }
    Q_INVOKABLE QDateTime   time()          { return m_date; }
    Q_INVOKABLE QString     text()          { return m_text; }
    Q_INVOKABLE QString     maxSuitablePhoto();
    Q_INVOKABLE QSize       maxSuitableSize();

    void setId(int id) { m_id = id; }
    void setAlbumId(int id) { m_albumId = id; }
    void setOwnerId(int id) { m_ownerId = id; }
    void setUserId(int id) { m_userId = id; }
    void setPhoto75(QString photo) { m_photo75 = photo; }
    void setPhoto130(QString photo) { m_photo130 = photo; }
    void setPhoto604(QString photo) { m_photo604 = photo; }
    void setPhoto807(QString photo) { m_photo807 = photo; }
    void setPhoto1280(QString photo) { m_photo1280 = photo; }
    void setPhoto2560(QString photo) { m_photo2560 = photo; }
    void setWidth(int width) { m_width = width; }
    void setHeight(int height) { m_height = height; }
    void setDate(QDateTime date) { m_date = date; }
    void setText(QString text) { m_text = text; }
private:
    QSize calculatePhotoSize(QSize size);
signals:

public slots:
private:
    int m_id;
    int m_albumId;
    int m_ownerId;
    int m_userId;
    QString m_photo75;
    QString m_photo130;
    QString m_photo604;
    QString m_photo807;
    QString m_photo1280;
    QString m_photo2560;
    QString m_text;
    int m_width;
    int m_height;
    QDateTime m_date;
};

#endif // VKCONTAINERPHOTO_H
