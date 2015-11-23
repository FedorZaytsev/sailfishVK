#ifndef VKCONTAINERCHATICON_H
#define VKCONTAINERCHATICON_H

#include <QObject>
#include <QDebug>
#include "vkabstractcontainer.h"

class VKContainerChatIcon : public VKAbstractContainer
{
    Q_OBJECT
public:
    explicit VKContainerChatIcon(VKStorage *storage, QObject *parent = 0);
    ~VKContainerChatIcon();
    void add(QString icon);
    Q_INVOKABLE QString get(int idx) const;
    static QString process(QString icon);
    QList<QString> icons() const;


    bool operator==(VKContainerChatIcon const& a);
    bool operator!=(VKContainerChatIcon const& a);
signals:

public slots:
private:
    QList<QString> m_icons;
};

#endif // VKCONTAINERCHATICON_H
