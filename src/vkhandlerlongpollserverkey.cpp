#include "vkhandlerlongpollserverkey.h"
#include "vklongpollserver.h"
#include "vk.h"

VKHandlerLongPollServerKey::VKHandlerLongPollServerKey(VK* vk, VKStorage* storage, QObject *parent) :
    VKAbstractHandler(storage, parent)
{
    m_vk = vk;
}

const QNetworkRequest VKHandlerLongPollServerKey::processRequest() {
    QString exec = QString(
"return {\"longPoll\":API.messages.getLongPollServer({\"use_ssl\":1,\"need_pts\":1})};"
);
    QList<QPair<QString,QString>> args;
    args.push_back({"code",exec});
    return generateRequest("execute", args);
}

void VKHandlerLongPollServerKey::processReply(QJsonValue *reply) {
    Q_UNUSED(reply);

    QJsonObject longPoll = reply->toObject().value("longPoll").toObject();

    m_vk->longPoll()->setKey(longPoll.value("key").toString());
    m_vk->longPoll()->setServer(longPoll.value("server").toString());
    if (updateTs()) {
        m_vk->longPoll()->setTs(longPoll.value("ts").toInt());
    }
    m_vk->longPoll()->setPts(longPoll.value("pts").toInt());

    if (!m_vk->longPoll()->initilized()) {
        m_vk->longPoll()->init(m_vk, storage());
    }
}
