#include "vkabstracthandler.h"

VKAbstractHandler::VKAbstractHandler(VKStorage* storage,QObject *parent) :
    QObject(parent)
{
    m_storage = storage;
    Q_ASSERT(parent);

}

QList<VKAbstractContainer *> VKAbstractHandler::data()
{
    return m_data;
}

VKStorage* VKAbstractHandler::storage() const {
    return m_storage;
}

const QNetworkRequest VKAbstractHandler::generateRequest(QString method, QList<QPair<QString,QString>>& args) {
    QUrl url(QString("https://api.vk.com/method/%1").arg(method));

    for (auto &e : args) {
        e.second = e.second.replace("+","%2B");
    }

    args.push_back({"access_token", storage()->accessToken()});
    args.push_back({"v","5.28"});

    QUrlQuery query;
    query.setQueryItems(args);
    url.setQuery(query);

    return QNetworkRequest(url);
}
