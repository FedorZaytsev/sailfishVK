import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    property bool showBusy

    width: Screen.width
    height: showBusy ? Screen.height/10 : 0
    BusyIndicator {
        anchors.centerIn: parent
        running: showBusy
    }
}
