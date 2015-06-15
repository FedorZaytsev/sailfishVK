#ifndef VKHANDLERLONGPOLLUPDATEDATA_H
#define VKHANDLERLONGPOLLUPDATEDATA_H

#include "vkabstracthandler.h"

class VKHandlerLongPollUpdateData : public VKAbstractHandler
{
    Q_OBJECT
public:
    explicit VKHandlerLongPollUpdateData(VKStorage* storage, QObject *parent = 0);
    virtual const QNetworkRequest processRequest();
    virtual bool processReply(QJsonObject*);
    virtual QString name() {return "";}
            void setUserIds(QList<QString> &userIds);
            void setMsgIds(QList<QString>& msgIds);
            //QList<VKContainerMessage*>& messages() {return m_messages;}
            //QList<VKContainerUser*>& users() {return m_users;}
            QJsonObject& data() {return m_data;}
signals:
    void dataReady();
public slots:
private:
    QList<QString> m_userIds;
    QList<QString> m_msgIds;
    
    QJsonObject m_data;
    //QList<VKContainerMessage*> m_messages;
    //QList<VKContainerUser*> m_users;
};

#endif // VKHANDLERLONGPOLLUPDATEDATA_H
