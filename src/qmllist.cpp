#include "qmllist.h"

QmlList::QmlList(QList<VKAbstractContainer*> list, QObject *parent) :
    QObject(parent)
{
    m_list = list;
}

QmlList::~QmlList() {
    qDeleteAll(m_list);
}

VKAbstractContainer *QmlList::at(int i) {
    return m_list.at(i);
}

int QmlList::count() {
    return m_list.count();
}
