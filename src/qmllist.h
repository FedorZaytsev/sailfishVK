#ifndef QMLLIST_H
#define QMLLIST_H

#include <QObject>
#include <QtAlgorithms>
#include "vkabstractcontainer.h"

class QmlList : public QObject
{
    Q_OBJECT
public:
    explicit QmlList(QList<VKAbstractContainer*> list, QObject *parent = 0);
    ~QmlList();
    VKAbstractContainer* at(int i);
    int count();
signals:

public slots:
private:
    QList<VKAbstractContainer*> m_list;
};

#endif // QMLLIST_H
