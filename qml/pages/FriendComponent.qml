import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    id: delegate
    property int user_id
    Image {
        id: avatar
        width: 100
        height: 100
        source: icon
    }
    Label {
        anchors.left: avatar.right
        text: name
    }

    Rectangle {
        x: Screen.width - Theme.paddingLarge - online.width
        y: avatar.height/2 - online.height/2
        id: online
        visible: isOnline
        width: 10
        height: 10
        radius: width*0.5
    }
}
