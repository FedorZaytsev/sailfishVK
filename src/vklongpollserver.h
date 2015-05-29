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
#include "vkabstracthandler.h"

//Long Poll server
//Have his own parser, network manager and so on

#include <QObject>
class VKStorage;
class VK;
class VKHandlerLongPollUpdateData;
class VKLongPollServer : public VKAbstractHandler
{
    Q_OBJECT
public:
    explicit VKLongPollServer(VKStorage *storage, QObject *parent = 0);
    void init(VK* vk, VKStorage* storage, QString key, QString server, int ts, int pts);
    bool initilized() {return key() != "" && ts() != 0;}
private:
    QString                 key() const                         {return m_key;}
    void                    setKey(const QString &key)          {m_key = key;}
    QString                 server() const                      {return m_server;}
    void                    setServer(const QString &server)    {m_server = server;}
    int                     ts() const                          {return m_ts;}
    void                    setTs(int ts)                       {m_ts = ts;}
    int                     pts() const                         {return m_pts;}
    void                    setPts(int pts)                     {m_pts = pts;}
    VKStorage*              storage() const                     {return m_storage;}
    void                    setStorage(VKStorage *storage)      {m_storage = storage;}
    QNetworkAccessManager&  manager()                           {return m_manager;}
    void                    setVK(VK *vk)                       {m_vk = vk;}
    VK*                     vk()                                {return m_vk;}
    void                    request();
    void                    processUpdate(QJsonArray &update);
    virtual const QNetworkRequest processRequest() {qCritical("never called"); return QNetworkRequest();}
    virtual bool processReply(QJsonObject*) {qCritical("never called"); return true;}
    virtual QString name() {return "longPollUpdate";}
    //void                    getUsersFromFwd(QString data, QSet<int> ids);

signals:

public slots:
    void networkDataReady(QNetworkReply* reply);
    void updateDataReady();
private:
    QNetworkAccessManager m_manager;
    QString m_key;
    QString m_server;
    int m_ts;
    int m_pts;
    VKStorage* m_storage;
    VK* m_vk;
    VKHandlerLongPollUpdateData* m_updateData;

    enum {
        VKUPDATE_MESSAGE_DELETE = 0,
        VKUPDATE_MESSAGE_FLAGS_CHANGE,
        VKUPDATE_MESSAGE_FLAGS_SET,
        VKUPDATE_MESSAGE_FLAGS_RESET,
        VKUPDATE_MESSAGE_NEW,
        VKUPDATE_MESSAGE_MARK_READ = 6,
        VKUPDATE_MESSAGE_MARK_READ2,
        VKUPDATE_USER_ONLINE,
        VKUPDATE_USER_OFFLINE,
        VKUPDATE_CHAT_UPDATED = 51,
        VKUPDATE_USER_TYPING = 61,
        VKUPDATE_CHAT_USER_TYPING,
        VKUPDATE_VIDEOCALL = 70,
        VKUPDATE_COUNTER_UPDATE = 80,

    };
};

#endif // VKLONGPOLLSERVER_H
