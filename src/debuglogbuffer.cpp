#include "debuglogbuffer.h"

DebugLogBuffer::DebugLogBuffer(QObject *parent) :
    QObject(parent)
{
    m_size = 0;
    m_linesSize = 0;
    m_ptr = 0;
    setMaxSize(5);
}

void DebugLogBuffer::setMaxSize(int size) {
    m_maxSize = size;
}

void DebugLogBuffer::add(QString line) {
    if (m_size < m_maxSize) {
        m_size++;
        m_data.append(line);
        m_linesSize += line.size();
    } else {
        if (m_ptr >= m_maxSize) {
            m_ptr = 0;
        }
        m_linesSize -= m_data[m_ptr].size();
        m_linesSize += line.size();
        m_data[m_ptr] = line;
        m_ptr++;
    }
}

QString DebugLogBuffer::generate() {
    QString result;

    for (int i=m_ptr;i<m_data.size();i++) {
        result += m_data[i] + "\n";
    }
    for (int i=0;i<m_ptr;i++) {
        result += m_data[i] + "\n";
    }
    return result;
}
