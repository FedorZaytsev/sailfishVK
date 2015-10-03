#include "vkstorage.h"
#include "vkcontainerchaticon.h"
#include "vkcontainerdialog.h"
#include "vkcontainermessage.h"
#include "vkcontaineruser.h"

VKStorage::VKStorage(QObject *parent) :
    QObject(parent)
{
    m_ourUserId = 0;
    m_savePath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)+"/data.dat";
    load();

}

VKStorage::~VKStorage()
{
    save();
    qDebug()<<"destruct storage";
}

void VKStorage::init() {
}


void VKStorage::addUser(QSharedPointer<VKContainerUser> user) {
    m_users[user->id()] = user;
    emit newUser(user->id(), user);
}

QSharedPointer<VKContainerUser> VKStorage::getUserById(int userId) {
    if (!m_users.contains(userId)) {
        qDebug()<<"no user with that id"<<userId;
        Q_ASSERT(0);
        return QSharedPointer<VKContainerUser>();
    }
    return m_users[userId];
}

VKContainerUser *VKStorage::getUserByIdPtr(int userId) {
    return getUserById(userId).data();
}

void VKStorage::addMessage(QSharedPointer<VKContainerMessage> message) {
    m_messages[message->id()] = message;

    auto it = std::lower_bound(m_sortedMessagesByDate.begin(), m_sortedMessagesByDate.end(), message, VKStorageComparator());
    m_sortedMessagesByDate.insert(it, message);

    emit newMessage(message->id(), message);
}

QSharedPointer<VKContainerMessage> VKStorage::getMessageById(int messageId) {
    if (!m_messages.contains(messageId)) {
        qDebug()<<"no message with that id"<<messageId;
        Q_ASSERT(0);
        return QSharedPointer<VKContainerMessage>();
    }
    return m_messages[messageId];
}

VKContainerMessage *VKStorage::getMessageByIdPtr(int messageId) {
    return getMessageById(messageId).data();
}

QSharedPointer<VKContainerMessage> VKStorage::getMessageSortedByTime(int idx) {
    if (idx >= m_sortedMessagesByDate.count()) {
        qDebug()<<"message with idx"<<idx<<"is not available. m_sortedMessagesByDate.count() =="<<m_sortedMessagesByDate.count();
        Q_ASSERT(0);
        return QSharedPointer<VKContainerMessage>();
    }

    return m_sortedMessagesByDate[idx];
}

void VKStorage::addDialog(QSharedPointer<VKContainerDialog> dialog) {
    m_dialogs[dialog->id()] = dialog;

    auto it = std::lower_bound(m_sortedDialogsByDate.begin(), m_sortedDialogsByDate.end(), dialog, VKStorageComparator());
    m_sortedDialogsByDate.insert(it, dialog);

    emit newDialog(dialog->id(), dialog);
}

QSharedPointer<VKContainerDialog> VKStorage::getDialogById(int dialogId) {
    if (!m_dialogs.contains(dialogId)) {
        qDebug()<<"no dialog with that id"<<dialogId;
        Q_ASSERT(0);
        return QSharedPointer<VKContainerDialog>();
    }

    return m_dialogs[dialogId];
}

VKContainerDialog *VKStorage::getDialogByIdPtr(int dialogId) {
    return getDialogById(dialogId).data();
}

QSharedPointer<VKContainerDialog> VKStorage::getDialogSortedByTime(int idx) {
    if (idx >= m_sortedDialogsByDate.count()) {
        qDebug()<<"dialog with idx"<<idx<<"is not available. m_sortedDialogsByDate.count() =="<<m_sortedDialogsByDate.count();
        Q_ASSERT(0);
        return QSharedPointer<VKContainerDialog>();
    }

    return m_sortedDialogsByDate[idx];
}

bool VKStorage::isAuthorizred() {
    return m_accessToken != "" && m_ourUserId != 0;
}

QString VKStorage::accessToken() const {
    return m_accessToken;
}

void VKStorage::setAccessToken(QString accessToken) {
    m_accessToken = accessToken;
}

bool VKStorage::userExist(int id) const {
    return m_users.contains(id);
}

int VKStorage::ourUserId() const {
    Q_ASSERT(m_ourUserId);
    return m_ourUserId;
}

void VKStorage::setOurUserId(int ourUserId) {
    m_ourUserId = ourUserId;
}

void VKStorage::save() {
    m_settings.setValue("token", m_accessToken);
    m_settings.setValue("userId", m_ourUserId);
}

void VKStorage::load() {
    m_accessToken = m_settings.value("token").toString();
    m_ourUserId = m_settings.value("userId").toInt();
}

void VKStorage::printOwnership()
{
    if (QQmlEngine::objectOwnership(this) == QQmlEngine::CppOwnership) {
        qDebug()<<"storage cpp";
    } else if (QQmlEngine::objectOwnership(this) == QQmlEngine::JavaScriptOwnership) {
        qDebug()<<"storage javascript";
    } else {
        qDebug()<<"storage unknown";
    }
}



