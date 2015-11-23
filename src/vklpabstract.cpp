#include "vklpabstract.h"

VKLPAbstract::VKLPAbstract(VKStorage *storage, QObject *parent) :
    IVKCompletable(parent)
{
    m_valid = false;
    m_type = VKLPEventType::INVALID;
    m_storage = storage;
}

void VKLPAbstract::complete(QVector<QSharedPointer<VKContainerDialog>> dialogs,
                            QVector<QSharedPointer<VKContainerMessage>> messages,
                            QVector<QSharedPointer<VKContainerUser>> users) {
    Q_UNUSED(dialogs);
    Q_UNUSED(messages);
    Q_UNUSED(users);
}
