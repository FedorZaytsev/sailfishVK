#ifndef VKLPMESSAGEDELETE_H
#define VKLPMESSAGEDELETE_H

#include "vklpabstract.h"
#include "vklpeventtype.h"
#include "vklpmessageflagsset.h"

class VKLPMessageDelete : public VKLPAbstract
{
    Q_OBJECT
public:
    explicit VKLPMessageDelete(VKStorage *storage, QObject *parent = 0);
    void fromLP(const QJsonArray &data);
    virtual bool needPreviousMessage();

signals:

public slots:
private:
    QSharedPointer<VKLPMessageFlagsSet> m_handler;
};

#endif // VKLPMESSAGEDELETE_H
