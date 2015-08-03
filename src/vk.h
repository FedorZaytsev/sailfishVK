#ifndef VK_H
#define VK_H

#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
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
#include "vkhandlermarkasread.h"
#include "pendingrequest.h"
#include "vkabstractcontainer.h"
#include "qmllist.h"
#include "vklongpollserver.h"
#include "vkhandlersendmessage.h"
#include "debuglogbuffer.h"

#define DEFAULT_TIME_REPEAT 3000        //3 sec

class VKLongPollServer;
class VKHandlerDialogs;

class VK : public QObject
{
    Q_OBJECT
public:
    explicit VK(QObject *parent = 0);
    ~VK();

    enum ErrorHandlers{
        ERROR_HANDLER_NOTHING,
        ERROR_HANDLER_RESTART,
        ERROR_HANDLER_RELOGIN,
        ERROR_HANDLER_INFORM
    };

    Q_ENUMS(ErrorHandlers)


    Q_INVOKABLE bool updateAccessToken(QString url);
    Q_INVOKABLE void getDialogs(int offset);
    Q_INVOKABLE void getMessages(int id, bool isChat, int offset);
    Q_INVOKABLE void markAsRead(QList<int> msgs);
    Q_INVOKABLE void sendMessage(int userId, bool isChat, QString text, QString forward, QString attachments);
    Q_INVOKABLE void dropAuthorization();
    Q_INVOKABLE QString getAuthPageUrl();
    Q_INVOKABLE VKStorage* getStorage() {return &storage();}
    Q_INVOKABLE bool isOurUserAuthorized();

                void sendNetworkRequest(VKAbstractHandler* handler);
                void errorHandler(QJsonObject, VKAbstractHandler*);
                void displayErrorMessage(QString err, ErrorHandlers displayType);
                void sendContainersToScript(VKAbstractHandler* handler);

                //debug
                void addDebugLogLine(const QString &line);
    Q_INVOKABLE QString generateBugReport();
    Q_INVOKABLE void assert0() {Q_ASSERT(0);}
    Q_INVOKABLE void inform() {emit displayError("test infrom message",ERROR_HANDLER_INFORM);}

signals:
    void handlerReady(QString name, VKAbstractHandler* handler);
    void displayError(QString reason, ErrorHandlers type);
public slots:
    void requestFinished(QNetworkReply*);
    void storageError(QString);
    void timerRequest(VKAbstractHandler* handler);
    void sendHandlertoScript(VKAbstractHandler* handler);
    void processHandler(VKAbstractHandler* handler);
private:
    VKStorage& storage() {return m_VKStorage;}
    QNetworkAccessManager *m_manager;
    VKStorage m_VKStorage;
    QMap<QNetworkReply*, VKAbstractHandler*> m_networkReplies;
    VKLongPollServer* m_longPoll;
    DebugLogBuffer* m_debugLogBuffer;
    bool m_isOnline;

    enum {
        ERROR_UNKNOWN = 1,
        ERROR_APP_TURNED_OFF,
        ERROR_UNKNOWN_METHOD,
        ERROR_WRONG_SIGNATURE,
        ERROR_AUTHORIZATION,
        ERROR_TOO_MANY_REQUESTS,
        ERROR_NO_PERMISSION,
        ERROR_WRONG_SYNTAX,
        ERROR_TOO_MANY_SIMILAR_REQUESTS,
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

};

#endif // VK_H
