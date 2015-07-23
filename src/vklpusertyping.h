#ifndef VKLPUSERTYPING_H
#define VKLPUSERTYPING_H

#include "vklpabstract.h"
#include "vkcontaineruser.h"

class VKLPUserTyping : public VKLPAbstract
{
    Q_OBJECT
public:
    explicit VKLPUserTyping(QObject *parent = 0);
    void fromLP(const QJsonArray &data, QList<QString> &l);
    virtual void complete(QVector<VKContainerDialog*> dialogs, QVector<VKContainerMessage*> messages, QVector<VKContainerUser*> users);

    Q_INVOKABLE int id() { return m_id; }
    Q_INVOKABLE int chatId() { return m_chatId; }
    Q_INVOKABLE QString userName() { return m_userName; }
signals:

public slots:
private:
    int m_id;
    int m_chatId;
    QString m_userName;
};

#endif // VKLPUSERTYPING_H
