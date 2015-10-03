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
        m_users.append(user);
    }

    //emit ready(this);
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

int VKHandlerUsers::count() {
    return m_users.count();
}

VKContainerUser *VKHandlerUsers::getPtr(int i) {
    return m_users.at(i).data();
}

QSharedPointer<VKContainerUser> VKHandlerUsers::get(int i) {
    return m_users.at(i);
}
