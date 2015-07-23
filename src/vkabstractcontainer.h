#ifndef VKABSTRACTCONTAINER_H
#define VKABSTRACTCONTAINER_H

#include <QObject>
#include <QDebug>

class VKAbstractContainer : public QObject
{
    Q_OBJECT
public:
    explicit VKAbstractContainer(QObject *parent = 0);
signals:

public slots:
private:
};

#endif // VKABSTRACTCONTAINER_H
