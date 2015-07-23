#include "vklpvideocall.h"

VKLPVideoCall::VKLPVideoCall(QObject *parent) :
    VKLPAbstract(parent)
{
    m_type = VKLPEventType::VIDEOCALL;
}

void VKLPVideoCall::fromLP(const QJsonArray &data) {
    Q_UNUSED(data);
    m_valid = true;
}
