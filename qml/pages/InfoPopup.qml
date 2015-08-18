/*
    Copyright (C) 2014 Ales Katona. Original code for InfoPopup taken
    from ownKeepass by Marko Koschak (marko.koschak@tisno.de)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0

MouseArea {
    id: infoPopup

    property bool enableTimeout: false
    property alias title: titleLabel.text
    property alias message: messageLabel.text

    function show(title, message, timeout, enableTimeout) {
        infoPopup.title = title
        infoPopup.message = message
        infoPopup.enableTimeout = enableTimeout
        if (timeout !== undefined)
            _timeout = timeout
        else
            _timeout = 5000 // set default
        if (infoPopup.enableTimeout) countdown.restart()
        state = "active"
    }
    function cancel() {
        _close()
        closed()
    }

    function _close() {
        if (enableTimeout) countdown.stop()
        state = ""
    }

    property int _timeout: 5000

    signal closed

    opacity: 0.0
    visible: false
    width: parent ? parent.width : Screen.width
    height: column.height + Theme.paddingMedium * 2 + colorShadow.height
    z: 1

    onClicked: cancel()

    states: State {
        name: "active"
        PropertyChanges { target: infoPopup; opacity: 1.0; visible: true }
    }
    transitions: [
        Transition {
            to: "active"
            SequentialAnimation {
                PropertyAction { target: infoPopup; properties: "visible" }
                FadeAnimation {}
            }
        },
        Transition {
            SequentialAnimation {
                FadeAnimation {}
                PropertyAction { target: infoPopup; property: "visible" }
            }
        }
    ]

    Rectangle {
        id: infoPopupBackground
        anchors.top: parent.top
        width: parent.width
        height: column.height + Theme.paddingMedium * 2
        color: Theme.highlightBackgroundColor
    }

    Rectangle {
        id: colorShadow
        anchors.top: infoPopupBackground.bottom
        width: parent.width
        height: column.height
        color: Theme.highlightBackgroundColor
    }

    OpacityRampEffect {
        sourceItem: colorShadow
        slope: 0.5
        offset: 0.0
        clampFactor: -0.5
        direction: 2 // TtB
    }

    Image {
        id: infoPopupIcon
        x: Theme.paddingSmall
        y: Theme.paddingLarge
        width: 48
        height: 36
        source: "image://theme/icon-system-warning"
        fillMode: Image.PreserveAspectFit
    }

    Column {
        id: column
        x: Theme.paddingSmall + infoPopupIcon.width + Theme.paddingMedium
        y: Theme.paddingMedium
        width: parent.width - Theme.paddingLarge - Theme.paddingSmall - infoPopupIcon.width - Theme.paddingMedium
        height: children.height
        Label {
            id: titleLabel
            width: parent.width
            horizontalAlignment: Text.AlignLeft
            font.family: Theme.fontFamilyHeading
            font.pixelSize: Theme.fontSizeLarge
            color: "black"
            opacity: 0.6
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        }
        Label {
            id: messageLabel
            width: parent.width
            horizontalAlignment: Text.AlignLeft
            font.family: Theme.fontFamily
            font.pixelSize: Theme.fontSizeExtraSmall
            color: "black"
            opacity: 0.5
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        }
    }

    Timer {
        id: countdown
        running: false
        repeat: false
        interval: infoPopup._timeout

        function restart() {
            running = false
            running = true
        }

        function stop() {
            running = false
        }

        onTriggered: _close()
    }
}
