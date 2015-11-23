#include "vklpvideocall.h"

VKLPVideoCall::VKLPVideoCall(VKStorage *storage, QObject *parent) :
    VKLPAbstract(storage, parent)
{
    m_type = VKLPEventType::VIDEOCALL;
}

void VKLPVideoCall::fromLP(const QJsonArray &data) {
    Q_UNUSED(data);
    m_valid = true;
}
