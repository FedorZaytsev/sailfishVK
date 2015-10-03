#ifndef VKCONTAINERATTACHMENTS_H
#define VKCONTAINERATTACHMENTS_H

#include <QJsonArray>
#include <QJsonObject>
#include <QSharedPointer>
#include "vkabstractcontainer.h"

class VKStorage;
class VKContainerAttachments : public VKAbstractContainer
{
    Q_OBJECT
public:


    enum AttachmentsType {
        PHOTO,
        VIDEO,
        AUDIO,
        DOC,
        WALL,
        WALL_REPLY,
        STICKER,
        LINK,
    };
    Q_ENUMS(AttachmentsType)

    explicit VKContainerAttachments(QObject *parent = 0);
    static QSharedPointer<VKContainerAttachments> fromJson(VKStorage *storage, QJsonArray obj, const QJsonArray users = QJsonArray());

    Q_INVOKABLE int count(AttachmentsType type);
    Q_INVOKABLE VKAbstractContainer* getPtr(AttachmentsType type, int i);
    Q_INVOKABLE QString description();


    QSharedPointer<VKAbstractContainer> get(AttachmentsType type, int i);

    void addAttachment(AttachmentsType type, QSharedPointer<VKAbstractContainer> container);

private:
    static VKContainerAttachments::AttachmentsType stringToType(QString type);
    static QString typeToString(AttachmentsType type);
    static QSharedPointer<VKAbstractContainer> getContainer(AttachmentsType type, VKStorage *storage, QJsonObject obj, QJsonArray users);
signals:

public slots:
private:
    QMap<AttachmentsType, QVector<QSharedPointer<VKAbstractContainer>>> m_data;
};

#endif // VKCONTAINERATTACHMENTS_H
