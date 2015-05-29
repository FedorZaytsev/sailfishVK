#ifndef VKLONGPOLLCONTAINER_H
#define VKLONGPOLLCONTAINER_H
#include <QVector>
#include <QString>


class VKLongPollContainer;
class VKLongPollContainer
{
public:
    VKLongPollContainer();
    QString messageId() const {return m_messageId;}
    void setMessageId(QString messageId) {m_messageId = messageId;}

    QString userId() const {return m_userId;}
    void setUserId(QString userId) {m_userId = userId;}

    void addFwd(VKLongPollContainer container) {m_fwd.append(container);}
    QVector<VKLongPollContainer>& fwd() {return m_fwd;}

private:
    QString m_messageId;
    QString m_userId;
    QVector<VKLongPollContainer> m_fwd;
};

#endif // VKLONGPOLLCONTAINER_H
