#ifndef VKSTORAGE_H
#define VKSTORAGE_H

#include <QObject>
#include <QSharedPointer>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QVariant>
#include <QFile>
#include <QStandardPaths>
#include <QDir>
#include <QSettings>
#include <QDebug>
#include <algorithm>
#include "vkstoragecomparator.h"
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

    void addUser(QSharedPointer<VKContainerUser> user);
    QSharedPointer<VKContainerUser> getUserById(int userId);
    Q_INVOKABLE VKContainerUser* getUserByIdPtr(int userId);

    void addMessage(QSharedPointer<VKContainerMessage> message);
    QSharedPointer<VKContainerMessage> getMessageById(int messageId);
    Q_INVOKABLE VKContainerMessage* getMessageByIdPtr(int messageId);
    QSharedPointer<VKContainerMessage> getMessageSortedByTime(int idx);

    void addDialog(QSharedPointer<VKContainerDialog> dialog);
    QSharedPointer<VKContainerDialog> getDialogById(int dialogId);
    Q_INVOKABLE VKContainerDialog* getDialogByIdPtr(int dialogId);
    QSharedPointer<VKContainerDialog> getDialogSortedByTime(int idx);

    bool userExist(int id) const;

    Q_INVOKABLE int ourUserId() const;
    void setOurUserId(int ourUserId);
    QString accessToken() const;
    void setAccessToken(const QString accessToken);
    bool isAuthorizred();

    void save();
    void load();

    Q_INVOKABLE void printOwnership();
private:

signals:
    void error(QString);
    void passToScript(QList<VKAbstractContainer*>);
    void newUser(int id, QSharedPointer<VKContainerUser>);
    void newMessage(int id, QSharedPointer<VKContainerMessage>);
    void newDialog(int id, QSharedPointer<VKContainerDialog>);
public slots:
private:
    QString     m_savePath;
    QString     m_accessToken;
    QSettings   m_settings;
    QMap<int, QSharedPointer<VKContainerDialog>> m_dialogs;
    QMap<int, QSharedPointer<VKContainerMessage>> m_messages;
    QMap<int, QSharedPointer<VKContainerUser>> m_users;

    QVector<QSharedPointer<VKContainerDialog>> m_sortedDialogsByDate;
    QVector<QSharedPointer<VKContainerMessage>> m_sortedMessagesByDate;
    int         m_ourUserId;
};

#endif // VKSTORAGE_H
