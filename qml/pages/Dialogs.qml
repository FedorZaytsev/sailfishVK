import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: dialogsPage
    property alias dialogListAlias : dialogsList
    property alias dialogsListModelAlias : dialogsListModel
    property int offset
    property bool ready: false

    function updatePage() {
        offset = 0
        dialogsList.model.clear()
        ready = false
        vk.getDialogs(0)
        console.log("dialogs page updated")
    }

    SilicaListView {
        id: dialogsList
        anchors.fill: parent

        PullDownMenu {
            MenuItem {
                text: "Exit"
                onClicked: {
                    pageStack.clear()
                    vk.dropAuthorization()
                    pageStack.push(Qt.resolvedUrl("Auth.qml"),{})
                }
            }
            MenuItem {
                text: "Report bug"
                onClicked: {
                    vk.assert0()
                }
            }
            MenuItem {
                text: "Update page"
                onClicked: {
                    vk.emitUpdatePages()
                }
            }
        }


        model: ListModel {
            id: dialogsListModel
        }
        spacing: Theme.paddingLarge
        header: PageHeader {
            id: pageHeader
            title: "Conversations"
        }
        footer: LoadingFooter {
            showBusy: dialogsList.model.count > 10
        }

        delegate: DialogComponent{}
        onMovementEnded: {
            if (visibleArea.yPosition + visibleArea.heightRatio > 0.99) {
                console.log("getDialogs scroll");
                vk.getDialogs(offset + 20)
            }
        }

        VerticalScrollDecorator {}
        Component.onCompleted: {
            vk.getDialogs(0)
        }
        BusyIndicator {
            anchors.centerIn: dialogsList
            running: !ready
            size: BusyIndicatorSize.Large
        }
        onModelChanged: {
            console.log("model changed!")
        }
    }
}
