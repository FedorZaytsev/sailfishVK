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
    height: {
        if (actionMessages !== "") {
            console.log("actionMessages", actionMessages,labelAction.height)
            return labelAction.height
        }

        var result = textHeight + avatarImage.height + padding + messageData.height
        if (index >= messagesList.model.count-1 || messagesList.model.get(index+1).offset === 0) {
            result = result + padding
        }
        return result
    }

    Component.onCompleted: {
        if (!isRead && id !== 0) {
            markAsRead(id)
            messagesList.model.setProperty(index, "isRead", true)
            //unreadRectangle.opacity = 0
        }
    }

    onCustomHighlightChanged: {
        highlighted = customHighlight
    }


    Item {
        x:  incoming ? avatarImage.width + itemOffset + 2*padding + Math.max(userNameId.contentWidth, dateId.contentWidth) :
                       maxWidth*(1 - labelSize) + itemOffset + Math.max(userNameId.width, dateId.width) - Math.max(userNameId.contentWidth, dateId.contentWidth) - width - padding
        width: userNameId.height + dateId.height
        height: userNameId.height + dateId.height
        visible: actionMessages === ""
        BusyIndicator {
            id: busy
            anchors.centerIn: parent
            running: id === -1
        }
    }

    Column {
        y: -Theme.paddingSmall
        visible: actionMessages === ""
        Label {
            id: userNameId
            x: incoming ? avatarImage.width + itemOffset + padding : maxWidth*(1 - labelSize) + itemOffset
            width: maxWidth * labelSize - avatarImage.width
            visible: actionMessages === ""
            font.pixelSize: Theme.fontSizeSmall
            color: Theme.primaryColor//incoming? Theme.primaryColor : Theme.highlightColor
            horizontalAlignment: incoming ? Text.AlignLeft : Text.AlignRight
            text: userName
        }
        Label {
            id: dateId
            x: incoming ? avatarImage.width + itemOffset + padding : maxWidth*(1 - labelSize) + itemOffset
            width: maxWidth * labelSize - avatarImage.width
            visible: actionMessages === ""
            font.pixelSize: Theme.fontSizeTiny
            color: Theme.primaryColor//incoming? Theme.secondaryColor : Theme.secondaryHighlightColor
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
        visible: actionMessages === ""
    }
    MessageData {
        id: messageData
        visible: actionMessages === ""
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
            while (idx < model.count) {
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
        visible: actionMessages === ""
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

    Label {
        id: labelAction
        width: maxWidth
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: Theme.fontSizeMedium
        visible: actionMessages !== ""
        wrapMode: Text.Wrap
        text: actionMessages
    }

}
