#ifndef CACHESTORAGE_H
#define CACHESTORAGE_H

#include <QObject>
#include <QMap>

class CacheStorage : public QObject
{
    Q_OBJECT
public:
    explicit CacheStorage(QObject *parent = 0);

signals:

public slots:
private:
};

#endif // CACHESTORAGE_H
