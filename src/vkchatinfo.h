#ifndef VKCHATDATA_H
#define VKCHATDATA_H

#include <QObject>
#include <QJsonObject>
#include <QVector>
#include <QDebug>

class VKChatInfo : public QObject
{
    Q_OBJECT
public:
    explicit VKChatInfo(QObject *parent = 0);

    bool            isChat() const;
    int             userId() const;
    int             chatId() const;
    QVector<int>    activeMemberIds() const;
    int             adminId() const;

    void            parseChatInfo(QJsonObject &message);

signals:

public slots:
private:
    bool            m_isChat;
    int             m_userId;
    int             m_chatId;
    QVector<int>    m_activeMemberIds;
    int             m_adminId;
};

#endif // VKCHATDATA_H
