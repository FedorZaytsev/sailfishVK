#include "vkabstracthandler.h"

VKAbstractHandler::VKAbstractHandler(VKStorage* storage,QObject *parent) :
    QObject(parent)
{
    m_storage = storage;
    m_additionalDataHandler = nullptr;
    Q_ASSERT(parent);
}

void VKAbstractHandler::requestAdditionInfo(VKAbstractHandler *h) {
    m_additionalDataHandler = h;
    //QObject::connect(m_additionalDataHandler, &VKAbstractHandler::ready, this, &VKAbstractHandler::additionDataReady);
    sendRequest(m_additionalDataHandler);
}

QJsonValue VKAbstractHandler::data() {
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

void VKAbstractHandler::additionDataReady(VKAbstractHandler *h) {
    Q_UNUSED(h);
    Q_ASSERT(0);

}
