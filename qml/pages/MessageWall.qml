import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: itm
    width: Screen.width
    height: column.height
    property var walls
    Column {
        id:column
        Repeater {
            id: repeater
            model: walls
            delegate: Item {
                width: Screen.width
                height: btn.height
                Button {
                    id: btn
                    anchors.horizontalCenter: parent.horizontalCenter
                    enabled: false
                    text: "Wall: Unsupported action"

                }
            }
        }
    }
}
