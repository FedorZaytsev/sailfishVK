#ifndef VKHANDLERLONGPOLLUPDATEDATA_H
#define VKHANDLERLONGPOLLUPDATEDATA_H

#include "vkabstracthandler.h"
#include "vklpabstract.h"

class VKContainerDialog;
class VKContainerMessage;
class VKContainerUser;
class VKHandlerLongPollUpdateData : public VKAbstractHandler
{
    Q_OBJECT
public:
    explicit VKHandlerLongPollUpdateData(VKStorage* storage, QObject *parent = 0);
    virtual const QNetworkRequest processRequest();
    virtual void processReply(QJsonValue*);
    virtual QString name() {return "longPoll";}
            void setUserIds(QList<QString> &userIds);
            void setMsgIds(QList<QString> &msgIds);
            void setChatIds(QList<QString> &chatIds);
            void setCheckIds(QList<QString> &checkIds);
            void setRemoved(QList<QString> &removed);
            void setEvents(QVector<QSharedPointer<VKLPAbstract>> events);
            QVector<QSharedPointer<VKLPAbstract>> events();
            QVector<QSharedPointer<VKContainerDialog>>& dialogs();
            QVector<QSharedPointer<VKContainerMessage>>& messages();
            QVector<QSharedPointer<VKContainerUser>>& users();
signals:
            void ready(VKAbstractHandler* h);
public slots:
private:

    QList<QString> m_userIds;
    QList<QString> m_msgIds;
    QList<QString> m_chatIds;
    QList<QString> m_checkIds;
    QList<QString> m_removed;
    QVector<QSharedPointer<VKLPAbstract>> m_events;

    QVector<QSharedPointer<VKContainerDialog>> m_updateDialogs;
    QVector<QSharedPointer<VKContainerMessage>> m_updateMessages;
    QVector<QSharedPointer<VKContainerUser>> m_updateUsers;

};

#endif // VKHANDLERLONGPOLLUPDATEDATA_H
