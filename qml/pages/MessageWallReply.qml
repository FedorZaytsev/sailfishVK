import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: itm
    width: Screen.width
    height: column.height
    property var wallReplies
    Column {
        id:column
        Repeater {
            id: repeater
            model: wallReplies
            delegate: Item {
                width: Screen.width
                height: btn.height
                Button {
                    id: btn
                    anchors.horizontalCenter: parent.horizontalCenter
                    enabled: false
                    text: "Wall Reply: Unsupported action"

                }
            }
        }
    }
}
