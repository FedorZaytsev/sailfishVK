#ifndef DEBUGLOGBUFFER_H
#define DEBUGLOGBUFFER_H

#include <QObject>

class DebugLogBuffer : public QObject
{
    Q_OBJECT
public:
    explicit DebugLogBuffer(QObject *parent = 0);
    void setMaxSize(int size);
    void add(QString line);
    QString generate();
signals:

public slots:
private:
    int m_size;
    int m_maxSize;
    int m_linesSize;
    int m_ptr;
    QList<QString> m_data;
};

#endif // DEBUGLOGBUFFER_H
