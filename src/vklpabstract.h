#ifndef VKLPABSTRACT_H
#define VKLPABSTRACT_H

#include <QObject>
#include <QJsonArray>
#include "vklpeventtype.h"
#include "vkcontainerdialog.h"
#include "vkcontainermessage.h"
#include "vkcontaineruser.h"
#include "ivkcompletable.h"

class VKLPAbstract : public IVKCompletable
{
    Q_OBJECT
public:
    explicit VKLPAbstract(VKStorage* storage, QObject *parent = 0);
    virtual void complete(QVector<QSharedPointer<VKContainerDialog>> dialogs, QVector<QSharedPointer<VKContainerMessage>> messages, QVector<QSharedPointer<VKContainerUser>> users);
    bool isValid() { return m_valid; }
    Q_INVOKABLE int type() { return m_type; }

protected:
    VKStorage* storage() { return m_storage; }
signals:
public slots:
protected:
    bool m_valid;
    int m_type;
private:
    VKStorage* m_storage;
};

#endif // VKLPABSTRACT_H
