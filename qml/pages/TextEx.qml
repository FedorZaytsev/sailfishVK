import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.vk.VK 1.0

Label {
    property string body
    VKTextWrap {
        id: textWrapHelper
    }

    function update() {
        console.log("medium",Theme.fontSizeMedium, font.letterSpacing, font.pointSize)
        if (width > 0) {
            textWrapHelper.setFont(font.family, font.pointSize)
            text = textWrapHelper.process(body, width)

            if (text === "") {
                height = 0
            }
        }
    }

    onBodyChanged: {
        update()
    }
    onWidthChanged: {
        update()
    }

    Component.onCompleted: {
        if (text === "") {
            height = 0
        }
    }
    onFontChanged: {
        console.log("changed")
        textWrapHelper.setFont(parent.font.family, parent.font.pixelSize)
    }

    Rectangle {
        anchors.fill: parent
        border.color: "red"
        border.width: 2
        color: "transparent"
    }
}

