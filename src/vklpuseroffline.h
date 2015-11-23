#ifndef VKLPUSEROFFLINE_H
#define VKLPUSEROFFLINE_H

#include "vklpabstract.h"

class VKLPUserOffline : public VKLPAbstract
{
    Q_OBJECT
public:
    explicit VKLPUserOffline(VKStorage *storage, QObject *parent = 0);
    void fromLP(const QJsonArray &data);

    Q_INVOKABLE int userId() { return m_userId; }
    Q_INVOKABLE bool isByTimeout() { return m_timeout; }
signals:

public slots:
private:
    int m_userId;
    bool m_timeout;
};

#endif // VKLPUSEROFFLINE_H
