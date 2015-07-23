#ifndef VKLPMESSAGEFLAGSCHANGE_H
#define VKLPMESSAGEFLAGSCHANGE_H

#include "vklpabstract.h"
#include "vklpeventtype.h"
#include "vklpflags.h"

class VKLPMessageFlagsChange : public VKLPAbstract
{
    Q_OBJECT
public:
    explicit VKLPMessageFlagsChange(QObject *parent = 0);
    void fromLP(const QJsonArray &data);

    Q_INVOKABLE int             id()                            { return m_id; }
    Q_INVOKABLE VKLPFlags*      flags()                         { return m_flags; }
    Q_INVOKABLE int             userId()                        { return m_userId; }
    Q_INVOKABLE bool            isChat()                        { return m_isChat; }
signals:

public slots:
protected:
                void            setUserId(int id);
                void            setFlags(VKLPFlags* flags);
                void            setId(int arg)                  { m_id = arg; }
private:
    int m_id;
    VKLPFlags* m_flags;
    int m_userId;
    bool m_isChat;
};

#endif // VKLPMESSAGEFLAGSCHANGE_H
