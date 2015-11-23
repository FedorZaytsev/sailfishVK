#ifndef VKLPMESSAGEFLAGSSET_H
#define VKLPMESSAGEFLAGSSET_H

#include "vklpmessageflagschange.h"
#include "vklpeventtype.h"
#include "vklpflags.h"
#include "vkcontainermessage.h"

class VKLPMessageFlagsSet : public VKLPMessageFlagsChange
{
    Q_OBJECT
    typedef VKLPMessageFlagsChange super;
public:
    explicit VKLPMessageFlagsSet(VKStorage *storage, QObject *parent = 0);
    virtual void completed();
    virtual bool needPreviousMessage();
    virtual void    process();
signals:

public slots:
protected:
};

#endif // VKLPMESSAGEFLAGSSET_H
