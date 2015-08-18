import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.vk.VK 1.0

//Represents chat msg
Row {
    property bool needIcon
    property bool isHighlighted
    property real offset
    spacing: Theme.paddingSmall

    UserTypingHelper {
        id: helper
        property bool hideIcon: false
        property string textHelper

        onTextUpdated: {
            hideIcon = text !== ""
            textHelper = text
        }
    }

    function addUser(usr) {
        helper.addUser(usr)
    }

    Image {
        width: needIcon && !helper.hideIcon ? 50 : 0
        height: 50
        source: needIcon && !helper.hideIcon ? authorAvatar50 : ""
    }
    Label {
        id: msgLabel
        color: isHighlighted ? Theme.highlightColor : Theme.primaryColor
        text: !helper.hideIcon ? msg : helper.textHelper
        width: Screen.width - x - Theme.paddingMedium - offset
        maximumLineCount: 1
        elide: Text.ElideRight
    }
}
