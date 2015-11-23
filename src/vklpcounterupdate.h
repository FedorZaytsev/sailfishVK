#ifndef VKLPCOUNTERUPDATE_H
#define VKLPCOUNTERUPDATE_H

#include "vklpabstract.h"

class VKLPCounterUpdate : public VKLPAbstract
{
    Q_OBJECT
public:
    explicit VKLPCounterUpdate(VKStorage *storage, QObject *parent = 0);
    void fromLP(const QJsonArray &data);

    Q_INVOKABLE int count() { return m_count; }
signals:

public slots:
private:
    int m_count;
};

#endif // VKLPCOUNTERUPDATE_H
