#ifndef IVKCOMPLETABLE_H
#define IVKCOMPLETABLE_H

#include <QObject>

class IVKCompletable : public QObject
{
    Q_OBJECT
public:
    explicit IVKCompletable(QObject *parent = 0);
    virtual ~IVKCompletable();
    virtual void completed() {}
signals:

public slots:

};

#endif // IVKCOMPLETABLE_H
