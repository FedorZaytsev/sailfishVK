#ifndef VKLPUSERTYPING_H
#define VKLPUSERTYPING_H

#include "vklpabstract.h"
#include "vkcontaineruser.h"

class VKLPUserTyping : public VKLPAbstract
{
    Q_OBJECT
public:
    explicit VKLPUserTyping(VKStorage *storage, QObject *parent = 0);
    void fromLP(const QJsonArray &data);
    virtual void completed();
    virtual int parseChatId(int id);

    Q_INVOKABLE int id() { return m_id; }
    Q_INVOKABLE int chatId() { return m_chatId; }
signals:

public slots:
private:
    int m_id;
    int m_chatId;
    QDateTime m_time;
};

#endif // VKLPUSERTYPING_H
