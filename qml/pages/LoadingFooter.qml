import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    width: Screen.width
    height: Screen.height/10
    BusyIndicator {
        anchors.centerIn: parent
        running: true
    }
}
