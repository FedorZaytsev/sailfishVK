import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: imageViewPage

    function addImage(image) {
        console.assert(typeof image === "string")
        view.model.append({
                              imageSource: image,
                          })
    }

    SlideshowView {
        id: view
        anchors.fill: parent
        property Item _activeItem
        enabled: true

        model: ListModel {}
        delegate: ImageFullScreen {}

        onCurrentItemChanged: {
            console.log("")
            if (!moving && currentItem) {
                view._activeItem = currentItem
            }
        }
    }
}
