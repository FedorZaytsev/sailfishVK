#ifndef VKVISIBLEDIALOG_H
#define VKVISIBLEDIALOG_H

#include "vkvisibleobject.h"
#include "vkcontainerdialog.h"

class VKVisibleDialog : public VKVisibleObject
{
    Q_OBJECT
public:
    explicit VKVisibleDialog(QObject *parent = 0);

signals:

public slots:
private:
    QSharedPointer<VKContainerDialog> m_dialog;
};

#endif // VKVISIBLEDIALOG_H
