#include "vkhandlersendmessage.h"

VKHandlerSendMessage::VKHandlerSendMessage(VKStorage *storage, QObject *parent) :
    VKAbstractHandler(storage, parent)
{
    m_messageId = 0;
    m_isChat = false;
    m_userId = 0;
    m_guid = 1;
}

const QNetworkRequest VKHandlerSendMessage::processRequest() {
    qDebug()<<m_userId<<m_text<<"guid"<<m_guid<<"m_attachments"<<m_attachments<<"m_forward"<<m_forward;

    QString attachments;
    if (m_attachments.length()) {
        attachments = QString(",\"attachment\":%1").arg(m_attachments);
    }

    QString forward;
    if (m_forward.length()) {
        forward = QString(",\"forward_messages\":%1").arg(m_forward);
    }

    QString exec = QString(
"return {\"id\":API.messages.send({\"%1_id\":%2,\"message\":\"%3\",\"guid\":%4%5%6}),\"guid\":%4};")
            .arg(m_isChat ? "chat" : "user")
            .arg(m_userId)
            .arg(m_text)
            .arg(m_guid)
            .arg(attachments)
            .arg(forward);

    QList<QPair<QString,QString>> args;
    args.push_back({"code",exec});
    return generateRequest("execute", args);
}

void VKHandlerSendMessage::processReply(QJsonValue *reply) {
    m_messageId = reply->toObject().value("id").toInt();
    m_guid = reply->toObject().value("guid").toInt();

    //emit ready(this);
}

QString VKHandlerSendMessage::name() {
    return "sendMessage";
}
