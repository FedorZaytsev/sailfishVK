#ifndef VKLPABSTRACT_H
#define VKLPABSTRACT_H

#include <QObject>
#include <QJsonArray>
#include "vklpeventtype.h"
#include "vkcontainerdialog.h"
#include "vkcontainermessage.h"

class VKLPAbstract : public QObject
{
    Q_OBJECT
public:
    explicit VKLPAbstract(QObject *parent = 0);
    virtual void complete(QVector<QSharedPointer<VKContainerDialog>> dialogs, QVector<QSharedPointer<VKContainerMessage>> messages, QVector<QSharedPointer<VKContainerUser>> users);
    bool isValid() { return m_valid; }
    Q_INVOKABLE int type() { return m_type; }
signals:
public slots:
protected:
    bool m_valid;
    int m_type;
};

#endif // VKLPABSTRACT_H
