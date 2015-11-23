#ifndef VKLONGPOLLCONTAINER_H
#define VKLONGPOLLCONTAINER_H
#include <QVector>
#include <QString>


class VKLongPollContainer;
class VKLongPollContainer
{
public:
    VKLongPollContainer();
    int messageId() const {return m_messageId;}
    void setMessageId(int messageId) {m_messageId = messageId;}

    int userId() const {return m_userId;}
    void setUserId(int userId) {m_userId = userId;}

    void addFwd(VKLongPollContainer container) {m_fwd.append(container);}
    QVector<VKLongPollContainer>& fwd() {return m_fwd;}

private:
    int m_messageId;
    int m_userId;
    QVector<VKLongPollContainer> m_fwd;
};

#endif // VKLONGPOLLCONTAINER_H
