#ifndef VKHANDLERMESSAGES_H
#define VKHANDLERMESSAGES_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>
#include "vkcontainermessage.h"
#include "vkabstracthandler.h"
#include "vkhandlerusers.h"

class VKHandlerMessages : public VKAbstractHandler
{
    Q_OBJECT
public:
    explicit VKHandlerMessages(VKStorage* storage, QObject *parent = 0);

signals:

public slots:

};

#endif // VKHANDLERMESSAGES_H
