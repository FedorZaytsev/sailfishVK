#ifndef VKLPFLAGS_H
#define VKLPFLAGS_H

#include <QObject>
#include <QDebug>

class VKLPFlags : public QObject
{
    Q_OBJECT
public:

    enum Enum {
        UNREAD = 1<<0,
        OUTBOX = 1<<1,
        REPLIED = 1<<2,
        IMPORTANT = 1<<3,
        CHAT = 1<<4,
        FRIENDS = 1<<5,
        SPAM = 1<<6,
        DELETED = 1<<7,
        FIXED = 1<<8,
        MEDIA = 1<<9
    };

    Q_ENUMS(Enum)

    explicit VKLPFlags(QObject *parent = 0);
    explicit VKLPFlags(int flags, QObject *parent = 0);
    void parseFlags(int flags);
    Q_INVOKABLE bool isSet(int arg);
    void set(int arg);
    void reset(int arg);
    Q_INVOKABLE void print();
signals:

public slots:
private:
    int m_flags;
};

#endif // VKLPFLAGS_H
