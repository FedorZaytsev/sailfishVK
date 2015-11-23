#ifndef VKLPMESSAGEMARKOUTCOMING_H
#define VKLPMESSAGEMARKOUTCOMING_H

#include "vklpmessagemarkincoming.h"

class VKLPMessageMarkOutcoming : public VKLPMessageMarkIncoming
{
    Q_OBJECT
public:
    explicit VKLPMessageMarkOutcoming(VKStorage *storage, QObject *parent = 0);
    virtual void mark();
signals:

public slots:

};

#endif // VKLPMESSAGEMARKOUTCOMING_H
