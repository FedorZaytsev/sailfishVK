import QtQuick 2.0
import Sailfish.Silica 1.0


Item {
    property real labelSize : 0.8
    property real padding : Theme.paddingSmall

    property var fwdMessages
    property string userName
    property string date
    property string msg
    property string icon
    property bool incoming
    property real textHeight
    property real childsheight
    height: avatarImage.height + textHeight + childsheight + padding
    width: Screen.width
    id: startColumn

    property real itemOffset: 2*padding
    property real offset: 0//2*padding

    x: 2*padding

    Component.onCompleted: {
        //console.log("component size",height)
    }

    Column {
        y: -Theme.paddingSmall
        Label {
            id: userNameId
            width: Screen.width * labelSize - avatarImage.width
            x: incoming ? avatarImage.width + itemOffset + padding + offset : Screen.width*(1 - labelSize) - offset - itemOffset - padding
            font.pixelSize: Theme.fontSizeSmall
            color: incoming? Theme.primaryColor : Theme.highlightColor
            horizontalAlignment: incoming ? Text.AlignLeft : Text.AlignRight
            text: userName
        }
        Label {
            width: Screen.width * labelSize - avatarImage.width
            x: incoming ? avatarImage.width + itemOffset + padding + offset : Screen.width*(1 - labelSize) - offset - itemOffset - padding
            font.pixelSize: Theme.fontSizeTiny
            color: incoming? Theme.primaryColor : Theme.highlightColor
            horizontalAlignment: incoming ? Text.AlignLeft : Text.AlignRight
            text: date
        }
    }


    Image {
        id: avatarImage
        x: incoming ? itemOffset + offset :  Screen.width - avatarImage.width - itemOffset - offset
        width: 50
        height: 50
        source: icon
    }
    Label {
        id: label
        x: incoming ? itemOffset + offset : Screen.width*(1 - labelSize) - itemOffset - offset
        anchors.top: avatarImage.bottom
        width: Screen.width * labelSize - 3*padding
        font.pixelSize: Theme.fontSizeSmall
        text: msg
        color: incoming? Theme.primaryColor : Theme.highlightColor
        wrapMode: Text.Wrap
        horizontalAlignment: incoming ? Text.AlignLeft : Text.AlignRight
        onTextChanged: {
            textHeight = height
        }
    }

    Column {
        y: textHeight + avatarImage.height + padding
        width: Screen.width

        Repeater {
            width: Screen.width
            model: fwdMessages.count
            property real allItemsHeight
            Loader {
                width: Screen.width
                source: "MessageFwdElement.qml"
            }
            onCountChanged: {
                for (var i=0;i<count;i++) {

                    itemAt(i).item.userName = fwdMessages.get(i).userName
                    itemAt(i).item.date = fwdMessages.get(i).date
                    itemAt(i).item.msg = fwdMessages.get(i).msg
                    itemAt(i).item.icon = fwdMessages.get(i).icon
                    itemAt(i).item.incoming = incoming
                    itemAt(i).item.fwdMessages = fwdMessages.get(i).fwdMessages
                    itemAt(i).item.offset = 0//offset + 2*padding

                    allItemsHeight += itemAt(i).item.height
                }
                childsheight = allItemsHeight
            }
        }
    }

    Rectangle {
        x: incoming ? padding + offset - width : Screen.width - padding - offset
        width: 2
        color: Theme.secondaryHighlightColor
        height: parent.height
        Component.onCompleted: {
            console.log("offset",offset)
        }
    }
}

