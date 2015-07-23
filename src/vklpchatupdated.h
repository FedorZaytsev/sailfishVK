#ifndef VKLPCHATUPDATED_H
#define VKLPCHATUPDATED_H

#include "vklpabstract.h"

class VKLPChatUpdated : public VKLPAbstract
{
    Q_OBJECT
public:
    explicit VKLPChatUpdated(QObject *parent = 0);
    void fromLP(const QJsonArray &data);

    Q_INVOKABLE int chatId() { return m_chatId; }
    Q_INVOKABLE bool isByUser() { return m_byUser; }
signals:

public slots:
private:
    int m_chatId;
    bool m_byUser;
};

#endif // VKLPCHATUPDATED_H
