#include "vklpusertyping.h"
#include "vkcontainerdialog.h"
#include "vkhandlerusers.h"

VKLPUserTyping::VKLPUserTyping(VKStorage *storage, QObject *parent) :
    VKLPAbstract(storage, parent)
{
    m_type = VKLPEventType::USER_TYPING;
    m_id = 0;
    m_chatId = 0;
}

void VKLPUserTyping::fromLP(const QJsonArray &data) {

    m_id = data.at(1).toInt();
    m_chatId = parseChatId(data.at(2).toInt());

    if (!storage()->isContainsDialog(m_chatId)) {
        qDebug()<<"doesn't contains dialog"<<m_chatId;
        return;
    }

    if (storage()->isContainsUser(m_id)) {
        auto dialog = storage()->getDialogById(m_chatId);
        dialog->addUserTyping(storage()->getUserById(m_id));
        deleteLater();
    } else {
        auto handler = new VKHandlerUsers(storage());
        handler->setUsers({m_id});
        storage()->helper()->request(this, handler);
        m_time = QDateTime::currentDateTime();
    }

}

void VKLPUserTyping::completed() {
    Q_ASSERT(storage()->isContainsDialog(m_chatId));
    Q_ASSERT(storage()->isContainsUser(m_id));

    if (QDateTime::currentDateTime() < m_time.addSecs(5)) {
        auto dialog = storage()->getDialogById(m_chatId);
        u_int32_t time = m_time.addSecs(5).toMSecsSinceEpoch() - QDateTime::currentDateTime().toMSecsSinceEpoch();
        dialog->addUserTyping(storage()->getUserById(m_id), time);
    }
    deleteLater();
}

int VKLPUserTyping::parseChatId(int id) {
    return id;
}


