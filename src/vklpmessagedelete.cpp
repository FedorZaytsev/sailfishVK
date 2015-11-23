#include "vklpmessagedelete.h"

VKLPMessageDelete::VKLPMessageDelete(VKStorage *storage, QObject *parent) :
    VKLPAbstract(storage, parent)
{
}

void VKLPMessageDelete::fromLP(const QJsonArray &data) {

    m_handler = QSharedPointer<VKLPMessageFlagsSet>(new VKLPMessageFlagsSet(storage(), this));
    m_handler->setId(data.at(1).toInt());
    if (data.count() > 2) {
        m_handler->setUserId(data.at(2).toInt());
    }

    auto flags = QSharedPointer<VKLPFlags>(new VKLPFlags);
    flags->set(VKLPFlags::DELETED);
    m_handler->setFlags(flags);

    m_handler->process();

    m_valid = false;

}

bool VKLPMessageDelete::needPreviousMessage() {
    return m_handler->needPreviousMessage();
}
