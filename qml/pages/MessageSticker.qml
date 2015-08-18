import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: itm
    width: Screen.width
    height: column.height
    property var stickers
    Column {
        id:column
        Repeater {
            id: repeater
            model: stickers
            delegate: Item {
                width: Screen.width
                height: btn.height
                Button {
                    id: btn
                    anchors.horizontalCenter: parent.horizontalCenter
                    enabled: false
                    text: "Sticker: Unsupported action"

                }
            }
        }
    }
}
