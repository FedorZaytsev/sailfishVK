#ifndef VKLPMESSAGEFLAGSCHANGE_H
#define VKLPMESSAGEFLAGSCHANGE_H

#include "vklpabstract.h"
#include "vklpeventtype.h"
#include "vklpflags.h"

class VKLPMessageFlagsChange : public VKLPAbstract
{
    Q_OBJECT
public:
    explicit VKLPMessageFlagsChange(VKStorage *storage, QObject *parent = 0);
    void fromLP(const QJsonArray &data);
    virtual bool needPreviousMessage();

signals:

public slots:
public:
    int             id()                            { return m_id; }
    VKLPFlags*      flagsPtr()                      { return m_flags.data(); }
    int             userId()                        { return m_userId; }
    bool            isChat()                        { return m_isChat; }
    QSharedPointer<VKLPFlags>   flags()             { return m_flags; }
    void            setUserId(int id);
    void            setFlags(QSharedPointer<VKLPFlags> flags);
    void            setId(int arg)                  { m_id = arg; }

    virtual void    process();
private:
    int m_id;
    QSharedPointer<VKLPFlags> m_flags;
    int m_userId;
    bool m_isChat;
};

#endif // VKLPMESSAGEFLAGSCHANGE_H
