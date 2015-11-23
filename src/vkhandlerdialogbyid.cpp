#include "vkhandlerdialogbyid.h"
#include "vkcontainerdialog.h"

VKHandlerDialogById::VKHandlerDialogById(VKStorage* storage, QObject *parent) :
    VKAbstractHandler(storage, parent)
{
}

const QNetworkRequest VKHandlerDialogById::processRequest() {
    QStringList sl;
    for (auto e:m_messageIds) {
        sl.append(QString::number(e));
    }
    QString exec = QString(
"var chats = API.messages.getById({\"message_ids\":\"%1\"});"
"var i = 0;"
"var chatUsers = [];"
"while (i < chats.items.length) {"
    "var chat_active = chats.items[i].chat_active;"
    "var ids = [chat_active[0],chat_active[1],chat_active[2],chat_active[3]];"
    "var users = API.users.get({\"user_ids\":(ids+\",\"+chats.items[i].user_id), \"fields\":\"photo_50,photo_100\"});"
    "chatUsers = chatUsers + users;"
    "i = i+1;"
"}"
"return {\"chats\":chats,\"chatUsers\":chatUsers};").arg(sl.join(","));

    QList<QPair<QString,QString>> args;
    args.push_back({"code",exec});
    return generateRequest("execute", args);
}

void VKHandlerDialogById::processReply(QJsonValue *_reply) {
    auto reply = _reply->toObject();
    auto dialogs = reply.value("chats").toObject().value("items").toArray();
    auto users = reply.value("chatUsers").toArray();

    for (auto e: dialogs) {
        if (e.isObject()) {
            auto el = e.toObject();
            //if user_id == 0 then dialog do not have messages;
            if (el.value("user_id").toInt() != 0) {
                auto msg = VKContainerDialog::fromJson(storage(), e.toObject(), users);
                storage()->addDialog(msg);
            }
        }
    }

    emit ready(this);
}

QString VKHandlerDialogById::name() {
    return "dialogById";
}

void VKHandlerDialogById::merge(VKAbstractHandler *_handler) {
    auto handler = dynamic_cast<VKHandlerDialogById*>(_handler);
    Q_ASSERT(handler);
    if (handler) {
        auto v = handler->messageIds();
        for (auto e: v) {
            add(e);
        }
    }
}

void VKHandlerDialogById::add(int id) {
    if (!m_messageIds.contains(id)) {
        m_messageIds.append(id);
    }
}

QVector<int> VKHandlerDialogById::messageIds() {
    return m_messageIds;
}
