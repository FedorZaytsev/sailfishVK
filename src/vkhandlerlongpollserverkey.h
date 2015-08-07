#ifndef VKHANDLERLONGPOLLSERVERKEY_H
#define VKHANDLERLONGPOLLSERVERKEY_H

#include "vkabstracthandler.h"
#include "vkstorage.h"

class VK;
class VKHandlerLongPollServerKey : public VKAbstractHandler
{
    Q_OBJECT
public:
    explicit VKHandlerLongPollServerKey(VK* vk, VKStorage* storage, QObject *parent = 0);
    virtual const QNetworkRequest processRequest();
    virtual void processReply(QJsonValue *reply);
    virtual QString name() {return "longPollServerKey";}

    void setUpdateTs(bool up) { m_updateTs = up; }
    bool updateTs() { return m_updateTs; }

signals:

public slots:
private:
    VK* m_vk;
    bool m_updateTs;
};

#endif // VKHANDLERLONGPOLLSERVERKEY_H
