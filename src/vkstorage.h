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
#include "vkadditionalhelper.h"

class VKContainerDialog;
class VKContainerMessage;
class VKContainerUser;
class VK;
class VKStorage : public QObject
{
    Q_OBJECT
public:
    explicit VKStorage(QObject *parent = 0);
             ~VKStorage();
    void init(VK* vk);

    void addUser(QSharedPointer<VKContainerUser> user);
    QSharedPointer<VKContainerUser> getUserById(int userId);
    bool isContainsUser(int userId);

    void addMessage(QSharedPointer<VKContainerMessage> message);
    QSharedPointer<VKContainerMessage> getMessageById(int messageId);
    QSharedPointer<VKContainerMessage> getMessageSortedByTime(int chatId, int idx);
    bool isContainsMessage(int idx);

    void addDialog(QSharedPointer<VKContainerDialog> dialog, bool addInSorted = true);
    QSharedPointer<VKContainerDialog> getDialogById(int dialogId);
    int sortedDialogsCount();
    QSharedPointer<VKContainerDialog> getDialogSortedByTime(int idx);
    bool isContainsDialog(int idx);



    bool userExist(int id) const;

    Q_INVOKABLE int ourUserId() const;
    void setOurUserId(int ourUserId);
    QString accessToken() const;
    void setAccessToken(const QString accessToken);
    bool isAuthorizred();

    void save();
    void load();

    Q_INVOKABLE void printOwnership();

    void onFirstMessageInDialogChanged(QSharedPointer<VKContainerDialog> dialog);
    VKAdditionalHelper *helper() const;

private:

    int removeDialogSorted(int id);
    int removeMessageSorted(int chatId, int id);
    int addMessageSorted(QSharedPointer<VKContainerMessage> message);
    int addDialogSorted(QSharedPointer<VKContainerDialog> dialog);
signals:
    void error(QString);
    void passToScript(QList<VKAbstractContainer*>);

    void newUser(int id, QSharedPointer<VKContainerUser>);
    void newMessage(int id, QSharedPointer<VKContainerMessage>);
    void newMessageSorted(int position, QSharedPointer<VKContainerMessage>);
    void newDialog(int id, QSharedPointer<VKContainerDialog>);
    void newDialogSorted(int position, QSharedPointer<VKContainerDialog>);

    void messageRemoved(int chatId, int position);

    void dialogNew(int idx, QSharedPointer<VKContainerDialog> dialog);
    void dialogMoved(int from, int to);
    void dialogRemoved(int idx);
public slots:
private:
    QString                                         m_savePath;
    QString                                         m_accessToken;
    QSettings                                       m_settings;
    QMap<int, QSharedPointer<VKContainerDialog>>    m_dialogs;
    QMap<int, QSharedPointer<VKContainerMessage>>   m_messages;
    QMap<int, QSharedPointer<VKContainerUser>>      m_users;
    VKAdditionalHelper*                             m_helper;
    QList<QSharedPointer<VKContainerDialog>>        m_sortedDialogsByDate;
    int                                             m_ourUserId;
};

#endif // VKSTORAGE_H
