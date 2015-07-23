#ifndef VKUSERTYPINGHELPER_H
#define VKUSERTYPINGHELPER_H

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QVector>
#include <QPair>
#include <QDebug>

#define TYPING_SECS_COUNT 5

class VKUserTypingHelper : public QObject
{
    Q_OBJECT
public:
    explicit VKUserTypingHelper(QObject *parent = 0);
    Q_INVOKABLE void addUser(QString user);
private:
    void calculateString();
signals:
    void textUpdated(QString text);
public slots:
    void timeout();
private:
    QMap<QString, QDateTime> m_users;
    QTimer m_timer;
    QString m_string;
};

#endif // VKUSERTYPINGHELPER_H
