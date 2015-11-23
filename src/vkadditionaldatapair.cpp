#include "vkadditionaldatapair.h"
#include "vkabstracthandler.h"

#include "vkcontainermessage.h"

VKAdditionalDataPair::VKAdditionalDataPair(IVKCompletable *completable, VKAbstractHandler *handler, QObject *parent) :
    QObject(parent)
{
    Q_ASSERT(handler);
    m_handler = handler;
    m_completables.append(completable);

    m_handler->setParent(this);
    QObject::connect(m_handler, &VKAbstractHandler::ready, this, &VKAdditionalDataPair::onReady);
}

VKAdditionalDataPair::~VKAdditionalDataPair() {
    fprintf(stderr, "destruction %p\n",this);
}

QVector<IVKCompletable *> VKAdditionalDataPair::completables() {
    return m_completables;
}

QString VKAdditionalDataPair::name() {
    return m_handler->metaObject()->className();
}

void VKAdditionalDataPair::add(IVKCompletable *completable, VKAbstractHandler *handler) {
    m_completables.append(completable);
    m_handler->merge(handler);
}

VKAbstractHandler *VKAdditionalDataPair::handler() {
    return m_handler;
}

void VKAdditionalDataPair::onReady(VKAbstractHandler *h) {
    Q_UNUSED(h);
    fprintf(stderr, "fprintf onReady %p\n", this);
    emit ready(this);
}
