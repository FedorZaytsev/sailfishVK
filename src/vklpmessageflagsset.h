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
    explicit VKLPMessageFlagsSet(QObject *parent = 0);
    void fromLP(const QJsonArray &data, QList<QString> &l);
    virtual void complete(QVector<VKContainerDialog*> dialogs, QVector<VKContainerMessage*> messages, QVector<VKContainerUser*> users);
    Q_INVOKABLE VKContainerMessage* message()           { return m_message; }

signals:

public slots:
protected:
    VKContainerMessage* m_message;
};

#endif // VKLPMESSAGEFLAGSSET_H
