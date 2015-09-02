import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {

    Label {
        width: Screen.width
        height: Screen.height
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: Theme.fontSizeMedium
        text: actionMessages
    }
    Component.onCompleted: console.log("ACTION COMPLETED",actionMessages)

}
