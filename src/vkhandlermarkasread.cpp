#include "vkhandlermarkasread.h"

VKHandlerMarkAsRead::VKHandlerMarkAsRead(VKStorage* storage, QObject *parent) :
    VKAbstractHandler(storage, parent)
{
}

const QNetworkRequest VKHandlerMarkAsRead::processRequest() {

    QStringList lst;
    for (auto e: m_ids) {
        lst.append(QString::number(e));
    }


    QString exec = QString(
"return API.messages.markAsRead({\"message_ids\":\"%1\"});"
).arg(lst.join(","));

    QList<QPair<QString,QString>> args;
    args.push_back({"code",exec});
    return generateRequest("execute", args);
}

void VKHandlerMarkAsRead::processReply(QJsonValue *reply) {

    if (reply->toInt() != 1) {
        qDebug()<<"restart handler";
        emit sendRequest(this);
    }

}

void VKHandlerMarkAsRead::setMsgs(QList<int> lst) {

    m_ids = lst;

}
