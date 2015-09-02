#ifndef VKLONGPOLLSERVER_H
#define VKLONGPOLLSERVER_H

#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QSet>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QObject>
#include <QPair>
#include <QTimer>
#include "vkabstracthandler.h"
#include "vklpeventtype.h"
#include "vklpabstract.h"

#include "vklpmessagedelete.h"
#include "vklpmessageflagschange.h"
#include "vklpmessageflagsreset.h"
#include "vklpmessageflagsset.h"
#include "vklpmessagenew.h"
#include "vklpmessagemarkincoming.h"
#include "vklpmessagemarkoutcoming.h"
#include "vklpuseroffline.h"
#include "vklpuseronline.h"
#include "vklpchatupdated.h"
#include "vklpusertyping.h"
#include "vklpchatusertyping.h"
#include "vklpcounterupdate.h"

#define MAX_USER_ID 2000000000
#define TIMEOUT_REQUEST (2*60*1000)
//Long Poll server
//Have his own parser, network manager and so on

class VKStorage;
class VK;
class VKHandlerLongPollUpdateData;
class VKLongPollServer : public VKAbstractHandler
{
    Q_OBJECT
public:
    explicit VKLongPollServer(VKStorage *storage, QObject *parent = 0);
    void                                init(VK* vk, VKStorage* storage);
    bool                                initilized() {return key() != "" && ts() != 0 && m_initialized;}

    virtual QString                     name() {return "longPollServer";}
    virtual const QNetworkRequest       processRequest() {qCritical("never called"); return QNetworkRequest();}
    virtual void                        processReply(QJsonValue*) {qCritical("never called");}

    Q_INVOKABLE int                     count();
    Q_INVOKABLE VKLPAbstract*           atPtr(int idx);
    Q_INVOKABLE void                    clean();

    QSharedPointer<VKLPAbstract>        at(int idx);


    void                                setKey(const QString &key)          {m_key = key;}
    void                                setServer(const QString &server)    {m_server = server;}
    void                                setTs(int ts)                       {m_ts = ts;}
    void                                setPts(int pts)                     {m_pts = pts;}
    void                                forceRequest();

    enum Enum {
        VKLP_REFRESH_HISTORY,
        VKLP_REFRESH_KEY,
        VKLP_REFRESH_KEY_AND_HISTORY
    };

private:
    QString                             key() const                         {return m_key;}
    QString                             server() const                      {return m_server;}
    int                                 ts() const                          {return m_ts;}
    int                                 pts() const                         {return m_pts;}
    VKStorage*                          storage() const                     {return m_storage;}
    void                                setStorage(VKStorage *storage)      {m_storage = storage;}
    QNetworkAccessManager&              manager()                           {return m_manager;}
    void                                setVK(VK *vk)                       {m_vk = vk;}
    VK*                                 vk()                                {return m_vk;}
    void                                processUpdate(QJsonArray &update, QList<QString> &userIds, QList<QString> &messageIds, QList<QString> &chatIds, QList<QString> &checkMessages, QList<QString> &removed);
    void                                sendUpdateDataRequest(QList<QString> &userIds, QList<QString> &messageIds, QList<QString> &chatIds, QList<QString> &checkMessages, QList<QString> &removed);
    QString                             type2string(VKLPEventType::E_VKUPDATE type);
    void                                updateReadyEvents();


signals:
    void updatePages();
public slots:
    void networkDataReady(QNetworkReply* reply);
    void updateDataReady(VKAbstractHandler* handler);
    void additionalInformationAboutUsersReady(VKAbstractHandler* handler);
    void watchdogTimer();
private:
    QNetworkAccessManager m_manager;
    QString m_key;
    QString m_server;
    int m_ts;
    int m_pts;
    VKStorage* m_storage;
    VK* m_vk;
    bool m_initialized;

    QMap<int, QVector<QSharedPointer<VKLPAbstract>>> m_cachedEvents;
    QVector<QSharedPointer<VKLPAbstract>> m_readyEvents;

    QVector<QSharedPointer<VKContainerDialog>> m_updateDialogs;
    QVector<QSharedPointer<VKContainerMessage>> m_updateMessages;
    QVector<QSharedPointer<VKContainerUser>> m_updateUsers;
    QTimer m_timer;
    QDateTime m_lastTime;
};

#endif // VKLONGPOLLSERVER_H
