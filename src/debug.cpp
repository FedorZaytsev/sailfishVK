#include "vk.h"
#include <QString>
#include <QDebug>

extern VK* __vk_object;

VK* getVK() {
    return __vk_object;
}

void vk_assert(const char *cond, const char *file, int line) {
    QString assert = QString("ASSERT: \"%1\" in file %2, line %3").arg(cond).arg(file).arg(line);
    qCritical("%s",assert.toLatin1().constData());
    QString reason = QString("Q_ASSERT(%1) in %2 file at %3 line").arg(cond).arg(file).arg(line);
    if (getVK()) {
        getVK()->displayErrorMessage(reason, VK::ERROR_HANDLER_RESTART);
    } else {
        qDebug()<<"cannot get VK object";
    }
}
