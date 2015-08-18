import QtQuick 2.0
import Sailfish.Silica 1.0
import "../handlers.js" as Handlers

BackgroundItem {
    id: backgrd
    property real labelSize : 0.8
    property real textHeight
    property bool customHighlight: highlight
    property real padding: Theme.paddingMedium
    property real itemOffset: 2*padding + offset*padding
    property real maxWidth: Screen.width - itemOffset*2
    property int  idx: index
    height: textHeight + avatarImage.height + 2*padding + messageData.height

    Component.onCompleted: {
        if (!isRead && id !== 0) {
            markAsRead(id)
            var model = Handlers.findDialogModel()
            var count = model.get(dialogIndex).unreadCount
            console.log("updating unread count")
            model.setProperty(dialogIndex, "unreadCount", count-1)
            isRead = true
        }
    }

    onCustomHighlightChanged: {
        highlighted = customHighlight
    }

    //Disabled
    Item {
        x:  incoming ? avatarImage.width + itemOffset + 2*padding + Math.max(userNameId.contentWidth, dateId.contentWidth) :
                       maxWidth*(1 - labelSize) + itemOffset + Math.max(userNameId.width, dateId.width) - Math.max(userNameId.contentWidth, dateId.contentWidth) - width - padding
        width: userNameId.height + dateId.height
        height: userNameId.height + dateId.height
        BusyIndicator {
            id: busy
            anchors.centerIn: parent
            running: false//id === 0
        }
    }

    Column {
        y: -Theme.paddingSmall
        Label {
            id: userNameId
            x: incoming ? avatarImage.width + itemOffset + padding : maxWidth*(1 - labelSize) + itemOffset
            width: maxWidth * labelSize - avatarImage.width
            font.pixelSize: Theme.fontSizeSmall
            color: incoming? Theme.primaryColor : Theme.highlightColor
            horizontalAlignment: incoming ? Text.AlignLeft : Text.AlignRight
            text: userName
        }
        Label {
            id: dateId
            x: incoming ? avatarImage.width + itemOffset + padding : maxWidth*(1 - labelSize) + itemOffset
            width: maxWidth * labelSize - avatarImage.width
            font.pixelSize: Theme.fontSizeTiny
            color: incoming? Theme.primaryColor : Theme.highlightColor
            horizontalAlignment: incoming ? Text.AlignLeft : Text.AlignRight
            text: date
        }
    }


    Image {
        id: avatarImage
        x: incoming ? itemOffset :  maxWidth - avatarImage.width + padding + itemOffset
        width: 50
        height: 50
        source: icon
    }
    MessageData {
        id: messageData
        anchors.top: avatarImage.bottom
        anchors.topMargin: padding
        anchors.bottomMargin: padding
        offset: itemOffset
    }


    onPressedChanged: {
        var idx = index+1
        var model = messagesList.model

        model.setProperty(index, "highlight", pressed)

        if (model.get(index).offset !== 0) {
            while (true) {
                model.setProperty(idx, "highlight", pressed)
                if (model.get(idx).offset === 0) break
                idx++
            }
        }

        idx = index-1
        while (idx >= 0 && model.get(idx).offset !== 0) {
            model.setProperty(idx, "highlight", pressed)
            idx--
        }

        messagesList.forceLayout()

    }

    Repeater {
        model: offset ? offset : 0
        delegate: Rectangle {
            x: incoming ? (index + 1)*padding + padding : maxWidth + padding + itemOffset + (index + 1)*padding
            width: 2
            color: Theme.secondaryHighlightColor
            height: {
                if ((backgrd.idx > 0 && (messagesList.model.get(backgrd.idx - 1).offset < offset)) || backgrd.idx === 0) {
                    return backgrd.height - padding
                }
                return backgrd.height


            }
        }
    }

}
