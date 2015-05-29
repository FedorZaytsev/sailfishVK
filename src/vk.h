#ifndef VK_H
#define VK_H

#include <QObject>
#include <QDebug>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include "cryptostorage.h"
#include <QSettings>
#include <QDir>
#include <QObject>
#include <QtQuick>
#include <QMap>
#include <QVector>
#include <QQmlListProperty>
#include "vkstorage.h"
#include "vkabstracthandler.h"
#include "vkhandlerdialogs.h"
#include "pendingrequest.h"
#include "vkabstractcontainer.h"
#include "qmllist.h"
#include "vklongpollserver.h"


#define DEFAULT_TIME_REPEAT 3000        //3 sec

class VKLongPollServer;
class VKHandlerDialogs;

class VK : public QObject
{
    Q_OBJECT
public:
    explicit VK(QObject *parent = 0);
    ~VK();
    Q_INVOKABLE bool updateAccessToken(QString url);
    Q_INVOKABLE void getDialogs(int offset);
    Q_INVOKABLE void getMessages(QString identification, QString additional, int id, bool isChat, int offset);
    Q_INVOKABLE void getFriends(QString identification, QString additional, int user_id);
    Q_INVOKABLE void getUserInformation(QString identification, QString additional, QString ids,QString fields);
    Q_INVOKABLE bool isOurUserAuthorized();
                bool initialized() {return true;}                                                                                      //remove
    Q_INVOKABLE void getLongPollHistory(QString identification, QString additional, int ts, int pts, int messageId);
                void sendRequest(QString method, QList<QPair<QString,QString>> args, QString identificator, QString additional);        //remove
                void sendNetworkRequest(VKAbstractHandler* handler);
    Q_INVOKABLE void subscribeLongPollServer(QString identification, QString additional, QString key, QString server, int ts);              //remove
    Q_INVOKABLE void getLongPollMessageInformation(QString identification, QString additional, QString userIds, QString fwdMessagesIds);    //remove
                void errorHandler(QJsonObject, VKAbstractHandler*);
                void displayErrorMessage(QString err, int displayType);
    Q_INVOKABLE QString getAuthPageUrl();
    Q_INVOKABLE void downloadImageToCache(QString url);
    Q_INVOKABLE VKStorage* getStorage() {return &storage();}
                void sendContainersToScript(VKAbstractHandler* handler);


signals:
    void replyReady(QString document, QString identificator, QString additional);
    void dataReady(VKAbstractContainer* data);
    void handlerReady(QString name, QmlList* data);
    void fileDownloaded(QString name, QString path);
    void needToUpdate();
public slots:
    void requestFinished(QNetworkReply*);
    void storageError(QString);
    void timerRequest(VKAbstractHandler* handler);
private:
    VKStorage& storage() {return m_VKStorage;}
    QNetworkAccessManager *m_manager;
    QMap<QNetworkReply*,QPair<QString,QString>> m_replies;          //remove
    QSettings m_settings;                                           //remove
    VKStorage m_VKStorage;
    QMap<QNetworkReply*, VKAbstractHandler*> m_networkReplies;
    QVector<QImage*> m_images;
    VKLongPollServer* m_longPoll;
    

    enum {
        ERROR_UNKNOWN = 1,
        ERROR_APP_TURNED_OFF,
        ERROR_UNKNOWN_METHOD,
        ERROR_WRONG_SIGNATURE,
        ERROR_AUTHORIZATION,
        ERROR_TOO_MANY_REQUESTS,
        ERROR_NO_PERMISSION,
        ERROR_WRONG_SYNTAX,
        ERROR_TOO_MANY_SIMILAR_REQUESTS,           //???
        ERROR_SERVER_ERROR,
        ERROR_TEST_MODE,
        ERROR_CAPTHA = 14,
        ERROR_ACCESS_DENIED,
        ERROR_HTTPS_ONLY,
        ERROR_REVALIDATE_USER,
        ERROR_METHOD_ONLY_FOR_STANDALONE = 20,
        ERROR_METHOD_ONLY_FOR_STANDALONE_OR_OPEN_API,
        ERROR_METHOD_TURNED_OFF = 23,
        ERROR_NEED_CONFORMATION,
        ERROR_METHOD_WRONG_PARAMS = 100,
        ERROR_WRONG_API_ID,
        ERROR_WRONG_USER_ID = 113,
        ERROR_WRONG_TIMESTAMP = 150,
        ERROR_ALBUM_ACCESS_DENIED = 200,
        ERROR_AUDIO_ACCESS_DENIED,
        ERROR_GROUP_ACCESS_DENIED = 203,
        ERROR_ALBUM_IS_FULL = 300,
        ERROR_COINS = 500,
        ERROR_ADVERTISEMENT_NO_PERMISSION = 600,
        ERROR_ADVERTISEMENT_ERROR = 603,
        ERROR_HTTPS_SAME = 1113,                        //The same as ERROR_HTTPS_ONLY, may be missunderstanding in documentation?
    };

    enum {
        ERROR_HANDLER_NOTHING,
        ERROR_HANDLER_RESTART,
        ERROR_HANDLER_INFORM,
        ERROR_HANDLER_RELOGIN,
        ERROR_HANDLER_RELOGIN_INFORM,
    };
};

#endif // VK_H
