#ifndef VKCONTAINERCHATICON_H
#define VKCONTAINERCHATICON_H

#include <QObject>
#include "vkabstractcontainer.h"

class VKContainerChatIcon : public VKAbstractContainer
{
    Q_OBJECT
public:
    explicit VKContainerChatIcon(QObject *parent = 0);
    void add(QString icon);
    Q_INVOKABLE QString get(int idx);
    static QString process(QString icon);
signals:

public slots:
private:
    QList<QString> m_icons;
};

#endif // VKCONTAINERCHATICON_H
