/*
  Copyright (C) 2015 Petr Vytovtov
  Contact: Petr Vytovtov <osanwe@protonmail.ch>
  All rights reserved.

  This file is part of Kat.

  Kat is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Kat is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Kat.  If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0


SilicaFlickable {
    property string img : imageSource
    property bool isZoomed : false

    id: imageContainer
    width: Screen.width
    height: Screen.height

    contentWidth: Screen.width
    contentHeight: Screen.height


    PinchArea {
        anchors.fill: parent

        property real initialWidth
        property real initialHeight

        pinch.minimumScale: 0.8
        pinch.maximumScale: 4.0

        Image {
            id: showedImage
            anchors.fill: parent
            source: img
            fillMode: Image.PreserveAspectFit
        }

        onPinchStarted: {
            initialWidth = imageContainer.contentWidth
            initialHeight = imageContainer.contentHeight
        }

        onPinchUpdated: {
            imageContainer.contentX += pinch.previousCenter.x - pinch.center.x
            imageContainer.contentY += pinch.previousCenter.y - pinch.center.y
            if ((initialWidth * pinch.scale >= Screen.width) || (initialHeight * pinch.scale  >= Screen.height)) {
                    imageContainer.resizeContent(initialWidth * pinch.scale, initialHeight * pinch.scale, pinch.center)
            }
        }

        onPinchFinished: {
            console.log("showedImage",showedImage.implicitWidth, showedImage.width, showedImage.sourceSize.width,initialWidth, initialHeight)
            imageContainer.returnToBounds()

            if ((imageContainer.visibleArea.xPosition + imageContainer.visibleArea.widthRatio) * width < Screen.width * 1.2) {
                imageContainer.resizeContent(Screen.width, Screen.height, Qt.point(Screen.width/2, Screen.height/2))
                imageContainer.returnToBounds()
                imageContainer.isZoomed = false
            } else {
                imageContainer.isZoomed = true
            }
        }
    }
}

