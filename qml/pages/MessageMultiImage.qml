import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    property var images
    property real maxSize : maxWidth * labelSize - offset
    width: Screen.width
    height: {
        if (images && images.length > 0) {
            if (labelIdentificator.text !== "") {
                return labelIdentificator.height + imageIdentificator.height + padding
            }
            return imageIdentificator.height + padding
        }
        return 0
    }

    function calculateSize(sourceSize, param, type) {
        if (Math.max(sourceSize.width, sourceSize.height) > maxSize) {
            var factor = maxSize / Math.max(sourceSize.width,sourceSize.height)
            console.log(sourceSize.width,sourceSize.height)
            console.log("calculateSize", param * factor, type)
            return param * factor
        }
        return param
    }

    Image {
        id: imageIdentificator
        x: incoming ? offset : maxWidth - width - offset
        fillMode: Image.PreserveAspectFit
        source: (images && images.length > 0) ? images[0].image : ""
        width: (images && images.length>0) ? calculateSize(images[0].imageSize, images[0].imageSize.width, "width") : 0
        height: (images && images.length>0) ? calculateSize(images[0].imageSize, images[0].imageSize.height, "height") : 0
        MouseArea {
            anchors.fill: parent
            onClicked: {
                var page = pageStack.push(Qt.resolvedUrl("ImageViewFullScreen.qml"),{})
                for (var i=0;i<images.length;i++) {
                    page.addImage(images[i].image)
                }
            }
        }

       onProgressChanged: {
           progressBar.value = progress*100
       }

       ProgressBar {
            id: progressBar
            visible: imageIdentificator.status === Image.Loading || imageIdentificator.status === Image.Error
            width: parent.width
            minimumValue: 0
            maximumValue: 100
            valueText: Math.floor(value)
            label: imageIdentificator.status === Image.Loading ? "Loading" : "Error"
       }
    }

    Label {
        id: labelIdentificator
        anchors.left: imageIdentificator.left
        anchors.right: imageIdentificator.right
        anchors.top: imageIdentificator.bottom
        horizontalAlignment: Text.AlignRight
        font.pixelSize: Theme.fontSizeTiny
        color: Theme.secondaryColor
        text: (images && images.length > 1) ? images.length + " images" : ""
    }
}



