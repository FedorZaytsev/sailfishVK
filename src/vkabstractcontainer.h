#ifndef VKABSTRACTCONTAINER_H
#define VKABSTRACTCONTAINER_H

#include <QObject>
#include <QDebug>
#include <QQmlEngine>

class VKAbstractHandler;
class VKAbstractContainer : public QObject
{
    Q_OBJECT
public:
    explicit VKAbstractContainer(QObject *parent = 0);
    virtual void complete(VKAbstractHandler* h);
    virtual void copyTo(VKAbstractContainer* container);

signals:

public slots:
private:
};

#endif // VKABSTRACTCONTAINER_H
