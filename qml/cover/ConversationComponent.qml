import QtQuick 2.0
import Sailfish.Silica 1.0


Column {
    property alias dialogName: dialog.text
    property alias messageText: message.text
    property bool isRead
    Label {
        id: message
        color: !isRead ? Theme.secondaryHighlightColor : Theme.secondaryColor
        text: ""
    }
    Label {
        id: dialog
        color: !isRead ? Theme.highlightColor : Theme.primaryColor
        text: ""
    }
}
