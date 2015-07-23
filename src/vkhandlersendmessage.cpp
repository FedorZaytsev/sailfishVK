#include "vkhandlersendmessage.h"

VKHandlerSendMessage::VKHandlerSendMessage(VKStorage *storage, QObject *parent) :
    VKAbstractHandler(storage, parent)
{
    m_messageId = 0;
    m_isChat = false;
    m_userId = 0;
}

const QNetworkRequest VKHandlerSendMessage::processRequest() {
    static int guid;
    qDebug()<<"guid"<<guid;

    QString exec = QString(
"return API.messages.send({\"%1_id\":%2,\"message\":%3,\"guid\":%4,\"attachment\":%5,\"forward_messages\":%6});"
).arg(m_isChat ? "chat" : "user").arg(m_userId).arg(m_text).arg(guid++).arg(m_attachments).arg(m_forward);


    QList<QPair<QString,QString>> args;
    args.push_back({"code",exec});
    return generateRequest("execute", args);
}

void VKHandlerSendMessage::processReply(QJsonValue *reply) {
    m_messageId = reply->toInt();

    emit ready(this);
}

QString VKHandlerSendMessage::name() {
    return "sendMessage";
}
