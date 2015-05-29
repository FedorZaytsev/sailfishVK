#ifndef PENDINGTIMER_H
#define PENDINGTIMER_H

#include <QTimer>
#include "vkabstracthandler.h"

class PendingRequest : public QObject
{
    Q_OBJECT
public:
    explicit PendingRequest(QObject *parent = 0);
    void request(VKAbstractHandler *handler);
    VKAbstractHandler *handler() const;

signals:
    void timeoutRequest(VKAbstractHandler* handler);
public slots:
    void timeout();
private:
    VKAbstractHandler *m_handler;
    QTimer m_timer;
};

#endif // PENDINGTIMER_H
