#ifndef VKHANDLERLONGPOLLUPDATEDATA_H
#define VKHANDLERLONGPOLLUPDATEDATA_H

#include "vkabstracthandler.h"

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

signals:
public slots:
private:

    QList<QString> m_userIds;
    QList<QString> m_msgIds;
    QList<QString> m_chatIds;
    QList<QString> m_checkIds;
    QList<QString> m_removed;

};

#endif // VKHANDLERLONGPOLLUPDATEDATA_H
