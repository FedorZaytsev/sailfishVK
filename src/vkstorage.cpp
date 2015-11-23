#include "vkstorage.h"
#include "vkcontainerchaticon.h"
#include "vkcontainerdialog.h"
#include "vkcontainermessage.h"
#include "vkcontaineruser.h"

VKStorage::VKStorage(QObject *parent) :
    QObject(parent)
{
    m_ourUserId = 0;
    m_helper = nullptr;
    m_savePath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)+"/data.dat";
    load();

}

VKStorage::~VKStorage()
{
    save();
    qDebug()<<"destruct storage";
}

void VKStorage::init(VK *vk) {
    m_helper = new VKAdditionalHelper(vk, this, this);
}


void VKStorage::addUser(QSharedPointer<VKContainerUser> user) {
    //FIXME
    qDebug()<<user->id()<<user->firstName()<<user->lastName();
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

bool VKStorage::isContainsUser(int userId) {
    return m_users.contains(userId);
}

void VKStorage::addMessage(QSharedPointer<VKContainerMessage> message) {
    //skip forwarded messages, because they doesn't have id
    if (message->id() == 0) {
        return;
    }
    if (m_messages.contains(message->id())) {
        auto &msg = m_messages[message->id()];
        msg->updateFrom(message);
        msg->emitChange();
        return;
    }
    m_messages[message->id()] = message;

    addMessageSorted(message);

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


QSharedPointer<VKContainerMessage> VKStorage::getMessageSortedByTime(int chatId, int idx) {
    Q_ASSERT(isContainsDialog(chatId));
    return getDialogById(chatId)->getMessageByIndex(idx);
}

bool VKStorage::isContainsMessage(int idx) {
    return m_messages.contains(idx);
}

void VKStorage::addDialog(QSharedPointer<VKContainerDialog> dialog, bool addInSorted) {
    if (m_dialogs.contains(dialog->id())) {
        auto &dlg = m_dialogs[dialog->id()];
        auto updated = dlg->updateFrom(dialog);
        if (updated) {
            dlg->emitChange();
        }
        return;
    }
    m_dialogs[dialog->id()] = dialog;

    if (addInSorted) {
        int pos = addDialogSorted(dialog);
        emit dialogNew(pos, dialog);
    }

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

QSharedPointer<VKContainerDialog> VKStorage::getDialogSortedByTime(int idx) {
    if (idx >= m_sortedDialogsByDate.count()) {
        qDebug()<<"dialog with idx"<<idx<<"is not available. m_sortedDialogsByDate.count() =="<<m_sortedDialogsByDate.count();
        Q_ASSERT(0);
        return QSharedPointer<VKContainerDialog>();
    }

    return m_sortedDialogsByDate[idx];
}

int VKStorage::sortedDialogsCount() {
    return m_sortedDialogsByDate.size();
}

bool VKStorage::isContainsDialog(int idx) {
    return m_dialogs.contains(idx);
}

void VKStorage::onFirstMessageInDialogChanged(QSharedPointer<VKContainerDialog> dialog) {
    Q_ASSERT(!dialog.isNull());

    if (dialog->isDeleted()) {
        int pos = removeDialogSorted(dialog->id());
        emit dialogRemoved(pos);
    } else {
        int pos = removeDialogSorted(dialog->id());
        int newPos = addDialogSorted(dialog);
        qDebug()<<dialog->debugDescription();
        if (pos == -1) {
            emit dialogNew(newPos, dialog);
        } else {
            emit dialogMoved(pos, newPos);
        }
    }
}

VKAdditionalHelper *VKStorage::helper() const {
    Q_ASSERT(m_helper != nullptr);
    return m_helper;
}

int VKStorage::removeDialogSorted(int id) {
    int idx = -1;
    qDebug()<<"removing"<<id;

    for (int i=0;i<m_sortedDialogsByDate.size();i++) {
        auto& el = m_sortedDialogsByDate.at(i);
        if (el->id() == id) {
            qDebug()<<el->id()<<el->chatName();
            idx = i;
            break;
        }
    }

    if (idx != -1) {
        m_sortedDialogsByDate.removeAt(idx);
    }

    return idx;
}

int VKStorage::removeMessageSorted(int chatId, int id) {
    Q_UNUSED(chatId);
    Q_UNUSED(id);
    Q_ASSERT(0);

    return 0;
}

int VKStorage::addMessageSorted(QSharedPointer<VKContainerMessage> message) {
    if (!isContainsDialog(message->chatId())) {
        qDebug()<<"adding template dialog";
        message->createTemplateDialog();
    }
    qDebug()<<message->debugDescription();
    auto dialog = getDialogById(message->chatId());
    int pos = dialog->appendMessage(message);

    qDebug()<<pos;

    emit newMessageSorted(pos, message);
    return pos;

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

int VKStorage::addDialogSorted(QSharedPointer<VKContainerDialog> dialog) {
    qDebug()<<dialog->debugDescription();

    auto it = std::lower_bound(m_sortedDialogsByDate.begin(), m_sortedDialogsByDate.end(), dialog, VKStorageComparator());
    int position = it - m_sortedDialogsByDate.begin();
    if (m_sortedDialogsByDate.size() <= position || dialog->id() != m_sortedDialogsByDate[position]->id()) {
        m_sortedDialogsByDate.insert(position, dialog);
    }

    return position;
}






