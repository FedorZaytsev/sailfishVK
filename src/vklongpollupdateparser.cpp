#include "vklongpollupdateparser.h"
#include "vklongpollcontainer.h"
#include <QDebug>

VKLongPollUpdateParser::VKLongPollUpdateParser(QObject *parent) :
    QObject(parent)
{
}

int VKLongPollUpdateParser::parseUserId(const QString &data, int position, QString& userId) {
    for (int i=position;i<data.length();i++) {
        if (data.at(i) == '_') {
            userId = data.mid(position, i-position);
            return i;
        }
    }
    userId = data.mid(position,data.length()-position);
    return data.length();
}

int VKLongPollUpdateParser::parseMsgId(const QString &data, int position, QString& msgId) {
    for (int i=position;i<data.length();i++) {
        if (data.at(i) == ',' || data.at(i) == ':' || data.at(i) == ')') {
            msgId = data.mid(position, i-position);
            return i;
        }
    }
    msgId = data.mid(position,data.length()-position);
    return data.length();
}


void VKLongPollUpdateParser::parse(QString data) {
    parseIds(data, 0, m_container);
    for (auto &e : container().fwd()) {
        m_topMessages.push_back(e.messageId());
    }
    debugPrint(m_container,"");
}

int VKLongPollUpdateParser::parseIds(const QString &data, int position, VKLongPollContainer &fwd) {

    while (position<data.length()) {
        qDebug()<<"while"<<data.mid(position,10);
        VKLongPollContainer c;
        
        QString userId = "1";
        position = parseUserId(data, position, userId);
        c.setUserId(userId);
        m_uniqueUsers.append(userId);


        QString msgId = "1";
        position = parseMsgId(data, position + 1, msgId);
        c.setMessageId(msgId);

        if (position == data.length()) {
            qDebug()<<"end1 add to"<<fwd.userId()<<c.userId();
            fwd.addFwd(c);
            qDebug()<<"1";
            break;
        }


        while (!data.at(position).isDigit()) {
            qDebug()<<"switch"<<data.at(position);
            switch (data.at(position).toLatin1()) {
                case ',': {
                    fwd.addFwd(c);
                    position++;
                } break;
                case ':': {
                    position = parseIds(data, position + 2, c);
                    qDebug()<<"after parseIds"<<position<<data.length();

                } break;
                case ')': {
                    fwd.addFwd(c);
                    return position + 1;
                } break;
                default: qDebug()<<"error";
            }
            if (position == data.length()) {
                qDebug()<<"end2 add to"<<fwd.userId()<<c.userId();
                fwd.addFwd(c);
                break;
            }
        }
    }
    return data.length();
}

void VKLongPollUpdateParser::debugPrint(VKLongPollContainer &c, QString separator) {
    qDebug()<<separator<<c.userId()<<c.messageId();
    for (auto &e : c.fwd()) {
        debugPrint(e,separator+"    ");
    }
}
