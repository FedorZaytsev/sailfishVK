#ifndef VKLPEVENTTYPE_H
#define VKLPEVENTTYPE_H

#include <QObject>

class VKLPEventType : public QObject
{
    Q_OBJECT
public:
    enum E_VKUPDATE{
        MESSAGE_DELETE = 0,
        MESSAGE_FLAGS_CHANGE,
        MESSAGE_FLAGS_SET,
        MESSAGE_FLAGS_RESET,
        MESSAGE_NEW,
        MESSAGE_MARK_READ_INCOMING = 6,
        MESSAGE_MARK_READ_OUTCOMING,
        USER_ONLINE,
        USER_OFFLINE,
        CHAT_UPDATED = 51,
        USER_TYPING = 61,
        CHAT_USER_TYPING,
        VIDEOCALL = 70,
        COUNTER_UPDATE = 80,
        INVALID = 255
    };
    Q_ENUMS(E_VKUPDATE)

    explicit VKLPEventType(QObject *parent = 0);

signals:

public slots:

};

#endif // VKLPEVENTTYPE_H
