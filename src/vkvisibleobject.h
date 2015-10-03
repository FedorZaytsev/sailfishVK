#ifndef VKVISIBLEOBJECT_H
#define VKVISIBLEOBJECT_H

#include <QObject>

class VKVisibleObject : public QObject
{
    Q_OBJECT
public:
    explicit VKVisibleObject(QObject *parent = 0);

signals:
    void paramIntChanged(QString param, int value);
    void paramBoolChanged(QString param, bool value);
    void paramStringChanged(QString param, QString value);
public slots:

};

#endif // VKVISIBLEOBJECT_H
