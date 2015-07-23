#ifndef VKLPMESSAGEFLAGSRESET_H
#define VKLPMESSAGEFLAGSRESET_H

#include "vklpmessageflagsset.h"
#include "vklpeventtype.h"
#include "vkcontainermessage.h"

class VKLPMessageFlagsReset : public VKLPMessageFlagsSet
{
    Q_OBJECT
public:
    explicit VKLPMessageFlagsReset(QObject *parent = 0);
signals:

public slots:

};

#endif // VKLPMESSAGEFLAGSRESET_H
