#include "vkadditionalhelper.h"
#include "vkhandlerusers.h"
#include "vkstorage.h"
#include "vk.h"
#include "vknetworkmanager.h"

VKAdditionalHelper::VKAdditionalHelper(VK *vk, VKStorage *storage, QObject *parent) :
    QObject(parent)
{
    m_storage = storage;
    m_vk = vk;
    start();
}

void VKAdditionalHelper::start() {
    qDebug()<<"starting";
    QObject::connect(&m_timer, &QTimer::timeout, this, &VKAdditionalHelper::onUpdate);
    m_timer.start(0);
}

void VKAdditionalHelper::request(IVKCompletable* completable, VKAbstractHandler* h) {

    QString hname = QString(h->metaObject()->className());

    if (m_data.contains(hname)) {
        qDebug()<<"merging handlers"<<hname;
        m_data[hname]->add(completable, h);
    } else {
        qDebug()<<"new handler"<<hname;
        m_data[hname] = new VKAdditionalDataPair(completable, h);
    }

}

void VKAdditionalHelper::onUpdate() {

    if (m_data.size() && !vk()->isNetworkBusy()) {
        qDebug()<<"requesting handler"<<m_data.keys()[0];
        auto key = m_data.keys()[0];
        auto el = m_data[key];

        QObject::connect(el, &VKAdditionalDataPair::ready, [] (VKAdditionalDataPair* pair){
            qDebug()<<"hadnler ready, calling completed";
            auto completables = pair->completables();
            for (auto e: completables) {
                if (e != nullptr) {
                    e->completed();
                }
            }
            pair->deleteLater();
        });
        vk()->sendNetworkRequest(el->handler());
        m_data.remove(key);
    }

}


