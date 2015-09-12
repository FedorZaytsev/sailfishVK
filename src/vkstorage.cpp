#include "vkstorage.h"
#include "vkcontainerchaticon.h"


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
    if (user->id() == ourUserId()) {
        m_ourUser = user;
        return;
    }
    Q_ASSERT(0);
}

QSharedPointer<VKContainerUser> VKStorage::getUserById(int userId) {
    if (userId == m_ourUserId) {
        return m_ourUser;
    }
    Q_ASSERT(0);
    return QSharedPointer<VKContainerUser>();
}

VKContainerUser *VKStorage::getUserByIdPtr(int userId) {
    return getUserById(userId).data();
}

void VKStorage::addMessage(QSharedPointer<VKContainerMessage> message) {
    Q_UNUSED(message);
    Q_ASSERT(0);
}

QSharedPointer<VKContainerMessage> VKStorage::getMessageById(int messageId) {
    Q_UNUSED(messageId);
    Q_ASSERT(0);

    return QSharedPointer<VKContainerMessage>();
}

void VKStorage::addDialog(QSharedPointer<VKContainerDialog> dialog) {
    Q_UNUSED(dialog);
    Q_ASSERT(0);
}

QSharedPointer<VKContainerDialog> VKStorage::getDialogById(int dialogId) {
    Q_UNUSED(dialogId);
    Q_ASSERT(0);

    return QSharedPointer<VKContainerDialog>();
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
    Q_UNUSED(id);
    Q_ASSERT(0);

    return NULL;
}

void VKStorage::getHistory() {
    Q_ASSERT(0);
}

int VKStorage::ourUserId() const {
    Q_ASSERT(m_ourUserId);
    return m_ourUserId;
}

void VKStorage::setOurUserId(int ourUserId) {
    m_ourUserId = ourUserId;

}

void VKStorage::debugPrint() {
    Q_ASSERT(0);

}

void VKStorage::save() {

    m_settings.setValue("token", m_accessToken);
    m_settings.setValue("userId", m_ourUserId);

}

void VKStorage::load() {

    m_accessToken = m_settings.value("token").toString();
    m_ourUserId = m_settings.value("userId").toInt();

    qDebug()<<m_accessToken;
}

int VKStorage::getUnread(int idx) {
    Q_ASSERT(0);
    qDebug()<<"get unread"<<idx;
    Q_ASSERT(idx);

    return 0;
}


