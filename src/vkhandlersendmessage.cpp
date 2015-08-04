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
    qDebug()<<m_userId<<m_text<<"guid"<<guid<<"m_attachments"<<m_attachments<<"m_forward"<<m_forward;

    QString attachments;
    if (m_attachments.length()) {
        attachments = QString(",\"attachment\":%1").arg(m_attachments);
    }

    QString forward;
    if (m_forward.length()) {
        forward = QString(",\"forward_messages\":%1").arg(m_forward);
    }

    QString exec = QString(
"return API.messages.send({\"%1_id\":%2,\"message\":\"%3\",\"guid\":%4%5%6});"
).arg(m_isChat ? "chat" : "user").arg(m_userId).arg(m_text).arg(guid++).arg(attachments).arg(forward);


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
