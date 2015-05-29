#ifndef VKPIXMAPPROVIDER_H
#define VKPIXMAPPROVIDER_H

#include <QQuickImageProvider>
#include <QDebug>
#include <QFile>
#include <QStandardPaths>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class VK;
class VKPixmapProvider : public QQuickImageProvider
{
public:
    explicit VKPixmapProvider(QQmlEngine* engine, ImageType type, Flags flags = 0);
    virtual QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

private:

    QQmlEngine* m_engine;
};

#endif // VKPIXMAPPROVIDER_H
