#ifndef VKADDITIONALDATA_H
#define VKADDITIONALDATA_H

#include <QObject>
#include <QTimer>
#include <QVector>
#include <QPair>
#include "vkabstractcontainer.h"
#include "vkadditionaldatapair.h"


/**
 * Class processing handler for a container or Long Poll handler via a packet request
 */
class VKStorage;
class VK;
class VKAdditionalHelper : public QObject
{
    Q_OBJECT
public:
    explicit VKAdditionalHelper(VK *vk, VKStorage* storage, QObject *parent = 0);
    void start();

    void request(IVKCompletable* completable, VKAbstractHandler* h);
private:
    VK* vk() { return m_vk; }
signals:

public slots:
    void onUpdate();
private:
    QMap<QString, VKAdditionalDataPair*> m_data;
    QTimer m_timer;
    VKStorage* m_storage;
    VK* m_vk;
};

#endif // VKADDITIONALDATA_H
