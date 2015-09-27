import QtQuick 2.0
import Sailfish.Silica 1.0


Column {
    property alias dialogName: dialog.text
    property alias messageText: message.text
    property bool isRead

    height: message.height + dialog.height
    Label {
        id: message
        width: parent.width
        color: !isRead ? Theme.secondaryHighlightColor : Theme.secondaryColor
        elide: Text.ElideRight
        font.pixelSize: Theme.fontSizeMedium
        text: ""
    }
    Label {
        id: dialog
        width: parent.width
        color: !isRead ? Theme.highlightColor : Theme.primaryColor
        elide: Text.ElideRight
        font.pixelSize: Theme.fontSizeSmall
        text: ""
    }
}
