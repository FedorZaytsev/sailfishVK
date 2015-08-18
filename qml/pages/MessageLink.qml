import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: itm
    width: Screen.width
    height: column.height
    property var links
    Column {
        id:column
        Repeater {
            id: repeater
            model: links
            delegate: Item {
                width: Screen.width
                height: btn.height
                Button {
                    id: btn
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Link: " + modelData.linkTitle
                    onClicked: {
                        Qt.openUrlExternally(modelData.linkUrl)
                    }
                }
            }
        }
    }
}
