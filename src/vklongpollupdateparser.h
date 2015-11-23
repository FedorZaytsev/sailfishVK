#ifndef VKLONGPOLLUPDATEPARSER_H
#define VKLONGPOLLUPDATEPARSER_H

#include <QObject>
#include <QSet>
#include "vklongpollcontainer.h"

class VKLongPollContainer;
class VKLongPollUpdateParser : public QObject
{
    Q_OBJECT
public:
    explicit VKLongPollUpdateParser(QObject *parent = 0);
    void parse(QString data);
    void parseMessage(const QString& data, int position);
    int parseUserId(const QString& data, int position, QString& userId);
    int parseMsgId(const QString& data, int position, QString& msgId);
    int parseIds(const QString& data, int position, VKLongPollContainer& fwd);
    int parseFwd(const QString& data, int position, VKLongPollContainer& fwd, int isStart);
    void debugPrint(VKLongPollContainer& c, QString separator);
    QVector<int> uniqueUsers() {return m_uniqueUsers;}
    QVector<int> topMessages() {return m_topMessages;}
    VKLongPollContainer& container() {return m_container;}
signals:

public slots:
private:
    VKLongPollContainer m_container;
    QVector<int> m_uniqueUsers;
    QVector<int> m_topMessages;
};

#endif // VKLONGPOLLUPDATEPARSER_H
