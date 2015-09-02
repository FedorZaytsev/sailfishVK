#include "vklpabstract.h"

VKLPAbstract::VKLPAbstract(QObject *parent) :
    QObject(parent)
{
    m_valid = false;
    m_type = VKLPEventType::INVALID;
}

void VKLPAbstract::complete(QVector<QSharedPointer<VKContainerDialog>> dialogs,
                            QVector<QSharedPointer<VKContainerMessage>> messages,
                            QVector<QSharedPointer<VKContainerUser>> users) {
    Q_UNUSED(dialogs);
    Q_UNUSED(messages);
    Q_UNUSED(users);
}
