#ifndef VKHEADERDIALOGS_H
#define VKHEADERDIALOGS_H

#include <QObject>
#include <QVariantList>
#include <QVariant>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include "vkabstracthandler.h"
#include "vkcontainerdialog.h"
#include "vkhandlermessages.h"

class VK;

class VKHandlerDialogs : public VKAbstractHandler
{
    Q_OBJECT
public:
    explicit VKHandlerDialogs(VKStorage* storage, QObject *parent = 0);
             ~VKHandlerDialogs();
    virtual const QNetworkRequest processRequest();
    virtual void processReply(QJsonValue *reply);
    virtual QString name();

    void setOffset(int offset);
    void setCount(int count);
    void setPreviewLength(int previewLength);
    void setUnread(int unread);
    void setLongPoll(bool b);

    QList<VKAbstractContainer*> &dialogs();
    Q_INVOKABLE VKAbstractContainer* at(int idx);
    Q_INVOKABLE int count();

signals:
    void unreadCountChanged(int count);
public slots:

private:
    u_int32_t m_offset;
    u_int32_t m_count;
    u_int32_t m_previewLength;
    u_int32_t m_unread;
    bool m_longPollRequested;
    QList<VKAbstractContainer*> m_dialogs;
};

#endif // VKHEADERDIALOGS_H
