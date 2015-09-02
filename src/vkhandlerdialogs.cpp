#include "vkhandlerdialogs.h"


//todo out_user_id


VKHandlerDialogs::VKHandlerDialogs(VKStorage *storage, QObject *parent) :
    VKAbstractHandler(storage, parent)
{
    Q_ASSERT(parent);
    m_offset = m_unread = 0;
    m_count = DEFAULT_COUNT;
    m_previewLength = DEFAULT_PREVIEW_LENGTH;
}

VKHandlerDialogs::~VKHandlerDialogs() {
}

const QNetworkRequest VKHandlerDialogs::processRequest() {
    Q_ASSERT(m_count >= 1 && m_count <= 200);
    QString exec = QString(
"var dialogs = API.messages.getDialogs({\"offset\":\"%1\",\"preview_length\":%2,\"count\":%3});"
"var i = 0;"
"var result = [];"
"while (i < dialogs.items.length) {"
    "var dialog = dialogs.items[i];"
    "var chat_act = dialog.message.chat_active;"
    "var ids = [chat_act[0],chat_act[1],chat_act[2],chat_act[3]];"
    "var users = API.users.get({\"user_ids\":(ids+\",\"+dialog.message.user_id), \"fields\":\"photo_50,photo_100,online,online_mobile\"});"
    "result.push({\"item\":dialog,\"users\":users});"
    "i = i+1;"
"}"
"return {\"user\":API.users.get({\"user_ids\":%4,\"fields\":\"photo_50,photo_100\"})[0],\"unreadCount\":dialogs.unread_dialogs,\"dialogs\":result};"
).arg(m_offset).arg(m_previewLength).arg(m_count).arg(m_storage->ourUserId());
    QList<QPair<QString,QString>> args;
    args.push_back({"code",exec});
    return generateRequest("execute", args);
}

void VKHandlerDialogs::processReply(QJsonValue *reply) {
    QJsonObject ourUser = reply->toObject().value("user").toObject();

    auto ourUserParsed = VKContainerUser::fromJson(storage(), ourUser);

    storage()->addUser(ourUserParsed);

    QJsonArray dialogs = reply->toObject().value("dialogs").toArray();

    QVector<int> unknownUsers;
    for (auto e : dialogs) {
        auto el = e.toObject();
        Q_ASSERT(el.value("item").isObject());
        Q_ASSERT(el.value("users").isArray());
        auto dialog = VKContainerDialog::fromJson(storage(), el.value("item").toObject(), el.value("users").toArray(), unknownUsers);
        m_dialogs.push_back(dialog);
    }

    setUnread(reply->toObject().value("unreadCount").toInt());

    //Additional request for case when we don't have info about users in fwd messages
    if (unknownUsers.length()) {
        qDebug()<<"We need additional users info about"<<unknownUsers;
        auto usersHandler = new VKHandlerUsers(storage(), this);
        usersHandler->setUsers(unknownUsers);
        requestAdditionInfo(usersHandler);
    } else {
        emit ready(this);
    }
}

QString VKHandlerDialogs::name() {
    return "dialogs";
}

void VKHandlerDialogs::setOffset(int offset) {
    m_offset = offset;
}

void VKHandlerDialogs::setCount(int count) {
    m_count = count;
}

void VKHandlerDialogs::setPreviewLength(int previewLength) {
    m_previewLength = previewLength;
}

void VKHandlerDialogs::setUnread(int unread) {
    m_unread = unread;
    emit unreadCountChanged(unread);
}

void VKHandlerDialogs::setLongPoll(bool b) {
    m_longPollRequested = b;
}

VKAbstractContainer* VKHandlerDialogs::atPtr(int idx) {
    return m_dialogs[idx].data();
}

int VKHandlerDialogs::count() {
    return m_dialogs.count();
}

QSharedPointer<VKAbstractContainer> VKHandlerDialogs::at(int idx) {
    return m_dialogs[idx];
}

void VKHandlerDialogs::additionDataReady(VKAbstractHandler *h) {
    auto handler = dynamic_cast<VKHandlerUsers*>(h);
    Q_ASSERT(handler != nullptr);

    qDebug()<<"additional info ready, updating";
    for (auto e: m_dialogs) {
        e->complete(handler);
    }

    emit ready(this);
}


