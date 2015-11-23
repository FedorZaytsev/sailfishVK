#ifndef VKLPMESSAGEMARKINCOMING_H
#define VKLPMESSAGEMARKINCOMING_H

#include "vklpabstract.h"
#include "vklpeventtype.h"

class VKLPMessageMarkIncoming : public VKLPAbstract
{
    Q_OBJECT
public:
    explicit VKLPMessageMarkIncoming(VKStorage *storage, QObject *parent = 0);
    void fromLP(const QJsonArray &data);

    virtual void mark();
signals:

public slots:
protected:
    int m_msgIdFrom;
    int m_msgIdTo;
};

#endif // VKLPMESSAGEMARKINCOMING_H
