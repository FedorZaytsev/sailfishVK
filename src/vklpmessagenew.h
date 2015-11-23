#ifndef VKLPMESSAGENEW_H
#define VKLPMESSAGENEW_H

#include "vklpabstract.h"
#include "vklpeventtype.h"
#include "vklongpollupdateparser.h"
#include "vkcontainerdialog.h"
#include "vkcontainermessage.h"
#include "vkcontainermessageaction.h"
#include "vklpflags.h"

class VKLPMessageNew : public VKLPAbstract
{
    Q_OBJECT
public:
    explicit VKLPMessageNew(VKStorage *storage, QObject *parent = 0);
    void fromLP(const QJsonArray &data);
    virtual void completed();
    Q_INVOKABLE int id() { return m_id; }
    Q_INVOKABLE bool isChat() { return m_isChat; }
    Q_INVOKABLE int userId() { return m_userId; }
signals:

public slots:
private:
    int m_id;
    bool m_isChat;
    bool m_addDialog;
    int m_userId;
    QSharedPointer<VKContainerMessage> m_message;
};

#endif // VKLPMESSAGENEW_H
