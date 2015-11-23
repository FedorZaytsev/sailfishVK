#include "vkhandlerusers.h"

VKHandlerUsers::VKHandlerUsers(VKStorage* storage, QObject *parent) :
    VKAbstractHandler(storage, parent)
{
    setFields("photo_50,photo_100");
}

const QNetworkRequest VKHandlerUsers::processRequest() {
    Q_ASSERT(m_userIds.length());
    Q_ASSERT(m_fields.length());

    QSet<int> set = QSet<int>::fromList(m_userIds.toList());
    QList<int> _l = set.toList();
    QStringList lst;
    for (auto e: _l) {
        lst.append(QString::number(e));
    }

    QString exec = QString(
"return API.users.get({\"user_ids\":\"%1\",\"fields\":\"%2\"});"
).arg(lst.join(",")).arg(m_fields);

    QList<QPair<QString,QString>> args;
    args.push_back({"code",exec});
    return generateRequest("execute", args);
}

void VKHandlerUsers::processReply(QJsonValue *reply) {
    auto users = reply->toArray();

    for (auto e: users) {
        auto user = VKContainerUser::fromJson(storage(), e.toObject());
        storage()->addUser(user);
    }

    emit ready(this);
}

QString VKHandlerUsers::name() {
    return "users";
}

void VKHandlerUsers::setUsers(QVector<int> ids) {

    m_userIds = ids;

}

void VKHandlerUsers::setFields(QString fields) {
    m_fields = fields;
}

QVector<int> VKHandlerUsers::users() {
    return m_userIds;
}

QString VKHandlerUsers::fields() {
    return m_fields;
}

void VKHandlerUsers::merge(VKAbstractHandler *h) {
    auto handler = dynamic_cast<VKHandlerUsers*>(h);
    Q_ASSERT(handler);
    if (handler) {
        setUsers( users() + handler->users() );

        setFields( mergeFields(fields(), handler->fields()) );
    }
}

QString VKHandlerUsers::mergeFields(QString f1, QString f2) {
    QSet<QString> flds;
    auto flds1 = f1.split(",");
    for (auto e:flds1) {
        flds.insert(e);
    }
    auto flds2 = f2.split(",");
    for (auto e:flds2) {
        flds.insert(e);
    }
    QStringList sl;
    for (auto e: flds) {
        sl.append(e);
    }
    return sl.join(",");
}
