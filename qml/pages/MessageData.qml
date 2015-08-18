import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    property real offset
    height: column.height


    Column {
        id: column
        spacing: 0
        Label {
            id: label
            x: incoming ? offset : maxWidth*(1 - labelSize) + offset + padding
            width: maxWidth * labelSize
            font.pixelSize: Theme.fontSizeMedium
            text: msg
            color: incoming? Theme.primaryColor : Theme.highlightColor
            wrapMode: Text.Wrap
            horizontalAlignment: incoming ? Text.AlignLeft : Text.AlignRight
            onTextChanged: {
                if (text === "") {
                    height = 0
                }
            }
            Component.onCompleted: {
                if (msg === "") {
                    height = 0
                }
            }
        }

        MessageMultiImage {
            id: multiimage
            images: attachments.photo
        }

        MessageVideo {
            id: messageVideo
            videos: attachments.video
        }

        MessageAudio {
            id: messageAudio
            audios: attachments.audio
        }

        MessageDocument {
            id: messageDoc
            documents: attachments.doc
        }

        MessageWall {
            id: messageWall
            walls: attachments.wall
        }

        MessageWallReply {
            id: messageWallReply
            wallReplies: attachments.wallReply
        }

        MessageSticker {
            id: messageSticker
            stickers: attachments.sticker
        }

        MessageLink {
            id: messageLink
            links: attachments.link
        }
    }
}
