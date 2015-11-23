#ifndef VKLPUNREADCOUNT_H
#define VKLPUNREADCOUNT_H

#include "vklpabstract.h"

class VKLPUnreadCount : public VKLPAbstract
{
    Q_OBJECT
public:
    explicit VKLPUnreadCount(VKStorage *storage, QObject *parent = 0);
    void fromLP(const QJsonArray &data);

    Q_INVOKABLE int count();

signals:

public slots:
private:
    int m_count;
};

#endif // VKLPUNREADCOUNT_H
