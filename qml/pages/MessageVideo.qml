import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: itm
    width: Screen.width
    height: column.height
    property var videos
    Column {
        id:column
        Repeater {
            id: repeater
            model: videos
            delegate: Item {
                width: Screen.width
                height: btn.height
                Button {
                    id: btn
                    anchors.horizontalCenter: parent.horizontalCenter
                    enabled: false
                    text: "Video: Unsupported action"
                    /*text: {
                        console.log("wert", modelData.videoUrl)
                        if (modelData.videoName.length>25) {
                            return "Video: "+modelData.videoName.substring(0,25)+"..."
                        }
                        return "Video: "+modelData.videoName
                    }
                    onClicked: {
                        //Qt.openUrlExternally("sms:?body=msgtosend")
                    }*/

                }
            }
        }
    }
}
