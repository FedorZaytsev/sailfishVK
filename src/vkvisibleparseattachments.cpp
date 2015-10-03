#include "vkvisibleparseattachments.h"

VKVisibleParseAttachments::VKVisibleParseAttachments(QObject *parent) :
    QObject(parent)
{
}

QVariantMap VKVisibleParseAttachments::parsePhoto(QSharedPointer<VKContainerPhoto> photo) {
    QVariantMap m;
    m["id"] = photo->id();
    m["image"] = photo->maxSuitablePhoto();
    m["imageSize"] = photo->maxSuitableSize();
    return m;
}

QVariantMap VKVisibleParseAttachments::parseVideo(QSharedPointer<VKContainerVideo> video) {
    QVariantMap m;
    m["videoId"] = video->id();
    m["videoName"] = video->title();
    m["videoUrl"] = video->playerUrl();
    return m;
}

QVariantMap VKVisibleParseAttachments::parseAudio(QSharedPointer<VKContainerAudio> audio) {
    QVariantMap m;
    m["audioId"] = audio->id();
    return m;
}

QVariantMap VKVisibleParseAttachments::parseDoc(QSharedPointer<VKContainerDocument> document) {
    QVariantMap m;
    m["documentId"] = document->id();
    return m;
}

QVariantMap VKVisibleParseAttachments::parseWall(QSharedPointer<VKContainerWall> wall) {
    Q_UNUSED(wall);
    QVariantMap m;
    return m;
}

QVariantMap VKVisibleParseAttachments::parseWallReply(QSharedPointer<VKContainerWallReply> wallReply) {
    Q_UNUSED(wallReply);
    QVariantMap m;
    return m;
}

QVariantMap VKVisibleParseAttachments::parseSticker(QSharedPointer<VKContainerSticker> sticker) {
    Q_UNUSED(sticker);
    QVariantMap m;
    return m;
}

QVariantMap VKVisibleParseAttachments::parseLink(QSharedPointer<VKContainerLink> link) {
    QVariantMap m;
    m["linkUrl"] = link->url();
    m["linkTitle"] = link->title();
    m["linkDescription"] = link->description();
    return m;
}

void VKVisibleParseAttachments::parse(QSharedPointer<VKContainerAttachments> attachments, QVariantMap &map) {

#define PARSE_ATTACHMENT(type, objtype, key, func) do{ \
    auto lst = QVariantList();\
    for(int i=0;i<attachments->count(VKContainerAttachments::type);i++) { \
        lst.append( func(attachments->get(VKContainerAttachments::type, i).dynamicCast<objtype>()) ); \
    }\
    map[key] = lst;\
    }while(0)


    PARSE_ATTACHMENT( PHOTO,         VKContainerPhoto,       "photo",        parsePhoto     );
    PARSE_ATTACHMENT( VIDEO,         VKContainerVideo,       "video",        parseVideo     );
    PARSE_ATTACHMENT( AUDIO,         VKContainerAudio,       "audio",        parseAudio     );
    PARSE_ATTACHMENT( DOC,           VKContainerDocument,    "doc",          parseDoc       );
    PARSE_ATTACHMENT( WALL,          VKContainerWall,        "wall",         parseWall      );
    PARSE_ATTACHMENT( WALL_REPLY,    VKContainerWallReply,   "wallReply",    parseWallReply );
    PARSE_ATTACHMENT( STICKER,       VKContainerSticker,     "sticker",      parseSticker   );
    PARSE_ATTACHMENT( LINK,          VKContainerLink,        "link",         parseLink      );

#undef PARSE_ATTACHMENT

}
