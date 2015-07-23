#ifndef VKLPMESSAGEMARKINCOMING_H
#define VKLPMESSAGEMARKINCOMING_H

#include "vklpabstract.h"
#include "vklpeventtype.h"

class VKLPMessageMarkIncoming : public VKLPAbstract
{
    Q_OBJECT
public:
    explicit VKLPMessageMarkIncoming(QObject *parent = 0);
    void fromLP(const QJsonArray &data);

    Q_INVOKABLE int userId() { return m_userId; }
    Q_INVOKABLE int untilMsg() { return m_msgId; }
signals:

public slots:
protected:
    void setUserId(int id);
private:
    int m_userId;
    bool m_isChat;
    int m_msgId;
};

#endif // VKLPMESSAGEMARKINCOMING_H
