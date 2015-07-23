#include "vklpflags.h"

VKLPFlags::VKLPFlags(QObject *parent) :
    QObject(parent)
{
    m_flags = 0;
}

VKLPFlags::VKLPFlags(int flags, QObject *parent) :
    QObject(parent)
{
    m_flags = flags;
}

void VKLPFlags::parseFlags(int flags) {
    m_flags = flags;
}

bool VKLPFlags::isSet(int arg) {
    return m_flags & arg;
}

void VKLPFlags::set(int arg) {
    m_flags |= arg;
}

void VKLPFlags::reset(int arg) {
    m_flags &= ~arg;
}

void VKLPFlags::print() {
    if (isSet(UNREAD)) qDebug()<<"UNREAD";
    if (isSet(OUTBOX)) qDebug()<<"OUTBOX";
    if (isSet(REPLIED)) qDebug()<<"REPLIED";
    if (isSet(IMPORTANT)) qDebug()<<"IMPORTANT";
    if (isSet(CHAT)) qDebug()<<"CHAT";
    if (isSet(FRIENDS)) qDebug()<<"FRIENDS";
    if (isSet(SPAM)) qDebug()<<"SPAM";
    if (isSet(DELETED)) qDebug()<<"DELETED";
    if (isSet(FIXED)) qDebug()<<"FIXED";
    if (isSet(MEDIA)) qDebug()<<"MEDIA";
}
