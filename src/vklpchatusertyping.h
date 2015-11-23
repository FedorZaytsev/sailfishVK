#ifndef VKLPCHATUSERTYPING_H
#define VKLPCHATUSERTYPING_H

#include "vklpusertyping.h"

class VKLPChatUserTyping : public VKLPUserTyping
{
    Q_OBJECT
public:
    explicit VKLPChatUserTyping(VKStorage *storage, QObject *parent = 0);
    virtual int parseChatId(int id);

signals:

public slots:

};

#endif // VKLPCHATUSERTYPING_H
