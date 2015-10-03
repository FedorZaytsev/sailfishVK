#ifndef VKVISIBLEPARSEATTACHMENTS_H
#define VKVISIBLEPARSEATTACHMENTS_H

#include <QObject>
#include "vkcontainerattachments.h"
#include "vkcontaineraudio.h"
#include "vkcontainerdocument.h"
#include "vkcontainerlink.h"
#include "vkcontainerphoto.h"
#include "vkcontainersticker.h"
#include "vkcontainervideo.h"
#include "vkcontainerwall.h"
#include "vkcontainerwallreply.h"

class VKVisibleParseAttachments : public QObject
{
    Q_OBJECT
public:
    explicit VKVisibleParseAttachments(QObject *parent = 0);
    void parse(QSharedPointer<VKContainerAttachments> attachments, QVariantMap &map);
private:
    QVariantMap parsePhoto(QSharedPointer<VKContainerPhoto> photo);
    QVariantMap parseVideo(QSharedPointer<VKContainerVideo> video);
    QVariantMap parseAudio(QSharedPointer<VKContainerAudio> audio);
    QVariantMap parseDoc(QSharedPointer<VKContainerDocument> document);
    QVariantMap parseWall(QSharedPointer<VKContainerWall> wall);
    QVariantMap parseWallReply(QSharedPointer<VKContainerWallReply> wallReply);
    QVariantMap parseSticker(QSharedPointer<VKContainerSticker> sticker);
    QVariantMap parseLink(QSharedPointer<VKContainerLink> link);
signals:

public slots:

};

#endif // VKVISIBLEPARSEATTACHMENTS_H
