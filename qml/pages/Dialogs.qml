import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.vk.VK 1.0

Page {
    id: dialogsPage
    objectName: "dialogsPage"
    property alias listAlias : dialogsList
    property int downloadCount: 20
    property bool ready: false

    function updatePage() {
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
            MenuItem {
                text: "test"
                onClicked: {
                    console.log("call test")
                    dialogsList.model.test()
                }
            }
        }


        model: VisualDialogModel{}
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
                console.log("getDialogs scroll", dialogsList.model.count());
                vk.getDialogs(dialogsList.model.count())
            }
        }

        VerticalScrollDecorator {}
        Component.onCompleted: {
            vk.getDialogs(0)
        }
        BusyIndicator {
            anchors.centerIn: dialogsList

            //We cannot change 'ready' property to comparing model.count with 0 because
            //They may be new in VK and without any dialogs
            //But I haven't tested this case, may be there will be another errors
            running: !ready
            size: BusyIndicatorSize.Large
        }
        onModelChanged: {
            console.log("model changed!")
        }
    }
}
