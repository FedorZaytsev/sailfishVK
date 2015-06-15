#include "vkpixmapprovider.h"
#include "vk.h"

VKPixmapProvider::VKPixmapProvider(QQmlEngine *engine, ImageType type, Flags flags) :
    QQuickImageProvider(type,flags)
{
    m_engine = engine;
}

QPixmap VKPixmapProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) {
    qDebug()<<"requestPixmap"<<id<<"Size"<<size->width()<<size->height()<<"requestedSize"<<requestedSize.width()<<requestedSize.height();

    QString filePath = QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + QUrl(id).path();
    QFile file(filePath);
    if (file.exists()) {
        qDebug()<<"file exists"<<filePath;
        return QPixmap(filePath);
    }

    //QQuickImageProvider *provider = static_cast<QQuickImageProvider*>(m_engine->imageProvider("id"));

    QPixmap pixmap(50, 50);
    pixmap.fill(Qt::transparent);

    return pixmap;
}
