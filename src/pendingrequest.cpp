#include "pendingrequest.h"

PendingRequest::PendingRequest(QObject *parent) :
    QObject(parent)
{
    QObject::connect(&m_timer,&QTimer::timeout,this,&PendingRequest::timeout);
}
VKAbstractHandler *PendingRequest::handler() const {
    return m_handler;
}

void PendingRequest::request(VKAbstractHandler *handler) {
    m_handler = handler;
    m_timer.start(3*1000);
}

void PendingRequest::timeout() {
    qDebug()<<"PendingRequest::timeout";
    emit timeoutRequest(m_handler);
    this->deleteLater();
}

