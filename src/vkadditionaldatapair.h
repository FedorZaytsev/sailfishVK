#ifndef VKADDITIONALDATAPAIR_H
#define VKADDITIONALDATAPAIR_H

#include <QObject>
#include <QSharedPointer>
#include "ivkcompletable.h"

class VKAbstractHandler;
class VKAdditionalDataPair : public QObject
{
    Q_OBJECT
public:
    explicit VKAdditionalDataPair(IVKCompletable* completable, VKAbstractHandler* handler, QObject *parent = 0);
    virtual ~VKAdditionalDataPair();
    QVector<IVKCompletable*> completables();
    VKAbstractHandler* handler();
    QString name();
    void add(IVKCompletable* completable, VKAbstractHandler* handler);



signals:
    void ready(VKAdditionalDataPair* data);
public slots:
    void onReady(VKAbstractHandler* h);
private:
    QVector<IVKCompletable*> m_completables;
    VKAbstractHandler* m_handler;
};

#endif // VKADDITIONALDATAPAIR_H
