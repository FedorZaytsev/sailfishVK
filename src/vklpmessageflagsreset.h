#ifndef VKLPMESSAGEFLAGSRESET_H
#define VKLPMESSAGEFLAGSRESET_H

#include "vklpmessageflagsset.h"
#include "vklpeventtype.h"
#include "vkcontainermessage.h"

class VKLPMessageFlagsReset : public VKLPMessageFlagsSet
{
    Q_OBJECT
public:
    explicit VKLPMessageFlagsReset(VKStorage *storage, QObject *parent = 0);
    virtual void completed();
    virtual bool needPreviousMessage();
    virtual void process();

signals:

public slots:

};

#endif // VKLPMESSAGEFLAGSRESET_H
