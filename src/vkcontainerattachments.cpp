#include "vkcontainerattachments.h"
#include "vkcontainerphoto.h"
#include "vkcontainervideo.h"
#include "vkcontaineraudio.h"
#include "vkcontainerdocument.h"
#include "vkcontainerwall.h"
#include "vkcontainerwallreply.h"
#include "vkcontainersticker.h"
#include "vkcontainerlink.h"

VKContainerAttachments::VKContainerAttachments(QObject *parent) :
    VKAbstractContainer(parent)
{
    m_type = eVKContainerAttachment;
}

QSharedPointer<VKContainerAttachments> VKContainerAttachments::fromJson(VKStorage *storage, QJsonArray obj, QJsonArray users) {
    auto attachments = QSharedPointer<VKContainerAttachments>(new VKContainerAttachments);

    for (auto e: obj) {
        auto el = e.toObject();
        auto type = stringToType(el.value("type").toString());
        attachments->addAttachment(type, getContainer(type, storage, el.value(el.value("type").toString()).toObject(), users));
    }
    return attachments;
}

int VKContainerAttachments::count(AttachmentsType type) {
    if (m_data.contains(type)) {
        return m_data[type].length();
    }
    return 0;
}

VKAbstractContainer* VKContainerAttachments::getPtr(AttachmentsType type, int i) {
    return m_data[type].at(i).data();
}


QSharedPointer<VKAbstractContainer> VKContainerAttachments::get(VKContainerAttachments::AttachmentsType type, int i) {
    return m_data[type].at(i);
}

QString VKContainerAttachments::description() {
    if (m_data.size()) {
        return typeToString( m_data.begin().key() );
    }
    return "";
}

void VKContainerAttachments::addAttachment(AttachmentsType type, QSharedPointer<VKAbstractContainer> container) {
    m_data[type].append(container);
}

VKContainerAttachments::AttachmentsType VKContainerAttachments::stringToType(QString type) {
    if (type == "audio") {
        return AttachmentsType::AUDIO;
    } else if (type == "doc") {
        return AttachmentsType::DOC;
    } else if (type == "photo") {
        return AttachmentsType::PHOTO;
    } else if (type == "sticker") {
        return AttachmentsType::STICKER;
    } else if (type == "video") {
        return AttachmentsType::VIDEO;
    } else if (type == "wall") {
        return AttachmentsType::WALL;
    } else if (type == "wall_reply") {
        return AttachmentsType::WALL_REPLY;
    } else if (type == "link") {
        return AttachmentsType::LINK;
    } else {
        qDebug()<<"unknown type"<<type;
        Q_ASSERT(0);
    }
    return AttachmentsType::PHOTO;
}

QString VKContainerAttachments::typeToString(AttachmentsType type) {
    if (type == AttachmentsType::AUDIO) {
        return "audio";
    } else if (type == AttachmentsType::DOC) {
        return "doc";
    } else if (type == AttachmentsType::PHOTO) {
        return "photo";
    } else if (type == AttachmentsType::STICKER) {
        return "sticker";
    } else if (type == AttachmentsType::VIDEO) {
        return "video";
    } else if (type == AttachmentsType::WALL) {
        return "wall";
    } else if (type == AttachmentsType::WALL_REPLY) {
        return "wall_reply";
    } else if (type == AttachmentsType::LINK) {
        return "link";
    } else {
        qDebug()<<"unknown type"<<type;
        Q_ASSERT(0);
    }
    return "unknown";
}

QSharedPointer<VKAbstractContainer> VKContainerAttachments::getContainer(AttachmentsType type, VKStorage* storage, QJsonObject obj, QJsonArray users) {

    switch(type) {
    case AttachmentsType::PHOTO: {
        return VKContainerPhoto::fromJson(storage, obj, users);
    } break;
    case AttachmentsType::VIDEO: {
        return VKContainerVideo::fromJson(storage, obj, users);
    } break;
    case AttachmentsType::DOC: {
        return VKContainerDocument::fromJson(storage, obj, users);
    } break;
    case AttachmentsType::AUDIO: {
        return VKContainerAudio::fromJson(storage, obj, users);
    } break;
    case AttachmentsType::STICKER: {
        return VKContainerSticker::fromJson(storage, obj, users);
    } break;
    case AttachmentsType::WALL: {
        return VKContainerWall::fromJson(storage, obj, users);
    } break;
    case AttachmentsType::WALL_REPLY: {
        return VKContainerWallReply::fromJson(storage, obj, users);
    } break;
    case AttachmentsType::LINK: {
        return VKContainerLink::fromJson(storage, obj, users);
    } break;
    default:
        Q_ASSERT(0);
        return QSharedPointer<VKAbstractContainer>();
    }
    return QSharedPointer<VKAbstractContainer>();
}
