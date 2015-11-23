#ifndef VKLPVIDEOCALL_H
#define VKLPVIDEOCALL_H

#include "vklpabstract.h"

class VKLPVideoCall : public VKLPAbstract
{
    Q_OBJECT
public:
    explicit VKLPVideoCall(VKStorage *storage, QObject *parent = 0);
    void fromLP(const QJsonArray &data);

signals:

public slots:

};

#endif // VKLPVIDEOCALL_H
