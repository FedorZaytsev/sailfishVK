#ifndef VKFILESTORAGE_H
#define VKFILESTORAGE_H

#include <QObject>
#include <QFile>

class VKFileStorage : public QObject
{
    Q_OBJECT
public:
    explicit VKFileStorage(QObject *parent = 0);

signals:

public slots:
private:
    QFile m_file;
};

#endif // VKFILESTORAGE_H
