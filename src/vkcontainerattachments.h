#ifndef VKCONTAINERATTACHMENTS_H
#define VKCONTAINERATTACHMENTS_H

#include <QJsonArray>
#include <QJsonObject>
#include <QSqlQuery>
#include "vkabstractcontainer.h"

class VKStorage;
class VKContainerPhoto;
class VKContainerVideo;
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
    static VKContainerAttachments*           fromJson(VKStorage *storage, QJsonArray obj, const QJsonArray users = QJsonArray());
    static VKContainerAttachments*           fromSql(VKStorage *storage, QSqlQuery query);

    //Q_INVOKABLE int countPhoto();
    //Q_INVOKABLE VKContainerPhoto* getPhoto(int i);
    //Q_INVOKABLE int countVideo();
    //Q_INVOKABLE VKContainerVideo* getVideo(int i);

    Q_INVOKABLE int count(AttachmentsType type);
    Q_INVOKABLE VKAbstractContainer* get(AttachmentsType type, int i);
    Q_INVOKABLE QString description();

    void addAttachment(AttachmentsType type, VKAbstractContainer* container);

private:
    static VKContainerAttachments::AttachmentsType stringToType(QString type);
    static QString typeToString(AttachmentsType type);
    static VKAbstractContainer* getContainer(AttachmentsType type, VKStorage *storage, QJsonObject obj, QJsonArray users);
signals:

public slots:
private:
    QMap<AttachmentsType, QVector<VKAbstractContainer*>> m_data;
};

#endif // VKCONTAINERATTACHMENTS_H
