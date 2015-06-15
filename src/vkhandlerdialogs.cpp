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

VKHandlerDialogs::~VKHandlerDialogs()
{
    for (auto el : m_data) {
        delete el;
    }
}

const QNetworkRequest VKHandlerDialogs::processRequest() {
    Q_ASSERT(m_count >= 20 && m_count <= 200);
    QString exec = QString(
"var dialogs = API.messages.getDialogs({\"offset\":\"%1\",\"preview_length\":%2,\"count\":%3});"
"var i = 0;"
"var result = [];"
"while (i < dialogs.items.length) {"
    "var dialog = dialogs.items[i];"
    "var chat_act = dialog.message.chat_active;"
    "var ids = [chat_act[0],chat_act[1],chat_act[2],chat_act[3]];"
    "var users = API.users.get({\"user_ids\":(ids+\",\"+dialog.message.user_id), \"fields\":\"photo_50,photo_100\"});"
    "result.push({\"item\":dialog,\"users\":users});"
    "i = i+1;"
"}"
"return {\"user\":API.users.get({\"user_ids\":%4,\"fields\":\"photo_50,photo_100\"})[0],\"dialogs\":result%5};"
                ).arg(m_offset).arg(m_previewLength).arg(m_count).arg(m_storage->ourUserId())
            .arg(m_longPollRequested ? ",\"longPoll\":API.messages.getLongPollServer({\"use_ssl\":1,\"need_pts\":1})" : "");
    QList<QPair<QString,QString>> args;
    args.push_back({"code",exec});
    return generateRequest("execute", args);
}

bool VKHandlerDialogs::processReply(QJsonObject *reply) {
    QJsonObject ourUser = reply->value("user").toObject();

    VKContainerUser* ourUserParsed = VKContainerUser::fromJson(storage(), ourUser);
    storage()->addUser(ourUserParsed);
    delete ourUserParsed;

    QJsonArray dialogs = reply->value("dialogs").toArray();

    for (auto e : dialogs) {
        auto el = e.toObject();
        Q_ASSERT(el.value("item").isObject());
        Q_ASSERT(el.value("users").isArray());
        VKContainerDialog* dialog = VKContainerDialog::fromJson(storage(), el.value("item").toObject(), el.value("users").toArray());
        storage()->addDialog(dialog);
        delete dialog;
    }
    storage()->debugPrint();
    return true;
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
    Q_ASSERT_X(0,"setUnread","setUnread function is not working properly");
    m_unread = unread;
}

void VKHandlerDialogs::setLongPoll(bool b) {
    m_longPollRequested = b;
}

