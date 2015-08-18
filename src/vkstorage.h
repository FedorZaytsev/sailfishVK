#ifndef VKSTORAGE_H
#define VKSTORAGE_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QVariant>
#include <QDebug>
#include "vkcontaineruser.h"
#include "vkcontainermessage.h"
#include "vkcontainerdialog.h"
#include "qmllist.h"

class VKContainerDialog;
class VKContainerMessage;
class VKContainerUser;
class VKStorage : public QObject
{
    Q_OBJECT
public:
    explicit VKStorage(QObject *parent = 0);
             ~VKStorage();
    void init();

    void addUser(VKContainerUser* user);
    VKContainerUser *getUserById(int userId);

    void addMessage(VKContainerMessage* message);
    VKContainerMessage* getMessageById(int messageId);

    void addDialog(VKContainerDialog* dialog);
    VKContainerDialog* getDialogById(int dialogId);
    QList<VKContainerDialog*> getDialogs(int offset);

    QString accessToken() const;
    void setAccessToken(const QString accessToken);

    bool userExist(int id) const;

    Q_INVOKABLE void getHistory();

    int ourUserId() const;
    void setOurUserId(int ourUserId);
    int getUnread(int idx);

    bool isAuthorizred();
    void debugPrint();

signals:
    void error(QString);
    void passToScript(QList<VKAbstractContainer*>);
public slots:
private:
    QMap<QString, QVector<QSqlQueryModel*>> m_models;
    QString     m_accessToken;
    VKContainerUser* m_ourUser;
    int         m_ourUserId;
};

#endif // VKSTORAGE_H
