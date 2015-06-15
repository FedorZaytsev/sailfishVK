#ifndef VKPIXMAPPROVIDER_H
#define VKPIXMAPPROVIDER_H

#include <QDeclarativeImageProvider>

class VKPixmapProvider : public QDeclarativeImageProvider
{
    Q_OBJECT
public:
    explicit VKPixmapProvider(QObject *parent = 0);

signals:

public slots:

};

#endif // VKPIXMAPPROVIDER_H
