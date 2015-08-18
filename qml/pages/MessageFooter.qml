import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.vk.VK 1.0

Item {
    property int usrId
    property bool isCht
    height: field.height + (label.visible ? label.height : 0)


    function addUser(usr) {
        helper.addUser(usr)
    }

    UserTypingHelper {
        id: helper
        onTextUpdated: {
            label.visible = text !== ""
            label.text = text
        }
    }

    Label {
        id: label
        width: Screen.width
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: Theme.fontSizeTiny
        maximumLineCount: 1
    }

    MessageField {
        id: field
        anchors.top: label.bottom
        userId: usrId
        chat: isCht
        width: parent.width
    }
}
