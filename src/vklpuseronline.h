#ifndef VKLPUSERONLINE_H
#define VKLPUSERONLINE_H

#include "vklpabstract.h"

class VKLPUserOnline : public VKLPAbstract
{
    Q_OBJECT
public:
    explicit VKLPUserOnline(QObject *parent = 0);
    void fromLP(const QJsonArray &data);

    enum Enum {
        UNKNOWN,
        MOBILE_UNKNOWN,
        IPHONE,
        IPAD,
        ANDROID,
        WPHONE,
        WINDOWS8,
        WEB
    };

    Q_INVOKABLE int userId() { return m_userId; }

signals:

public slots:
private:
    int m_userId;
    int m_device;
};

#endif // VKLPUSERONLINE_H
