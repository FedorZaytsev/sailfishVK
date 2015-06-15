#ifndef STORAGEASYNCHRONOUS_H
#define STORAGEASYNCHRONOUS_H

#include <QThread>
#include <QDebug>
#include <QQueue>

class StorageAsynchronous : public QThread
{
    Q_OBJECT
public:
    explicit StorageAsynchronous(QObject *parent = 0);

signals:

public slots:

};

#endif // STORAGEASYNCHRONOUS_H
