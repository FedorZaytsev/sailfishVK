import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: messages
    property string listHeader: "unknown"
    property string avatarUrl: ""
    property alias messagesListModel: messagesListModel
    property alias messagesList: messagesList
    property int id
    property int dialogIndex
    property int offsetTop : -1
    property int offsetBottom : -1
    property bool isChat
    property bool ready: false
    property var markAsReadArray: []

    onOffsetBottomChanged: {
        console.log(offsetBottom)
    }

    onOffsetTopChanged: {
        console.log(offsetTop)
    }

    function markAsRead(id) {
        markAsReadArray.push(id)
        console.log("length",markAsReadArray.length)
        if (markAsReadArray.length > 0) {
            markAsReadTimerId.start()
        }
    }
    function updatePage() {
        offset = 0
        ready = false
        markAsReadArray = []
        vk.getMessages(id,isChat,offset)
        console.log("messages page updated")
    }

    Timer {
        id: markAsReadTimerId
        repeat: false
        interval: 1000
        onTriggered: {
            console.log("timer triger",markAsReadArray)
            if (markAsReadArray.length  > 0) {
                //vk.markAsRead(markAsReadArray)
            }
            markAsReadArray = []
        }
    }

    SilicaListView {
        id: messagesList
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
        }
        ListModel {
            id: messagesListModel
        }
        model: messagesListModel
        spacing: Theme.paddingSmall
        footer: Column {
            PageHeader {
                id: pageHeader
                title: listHeader
            }
            LoadingFooter {
                showBusy: messagesList.model.count > 10
            }
        }
        header: MessageFooter {
            usrId: id
            isCht: isChat
            width: parent.width
        }

        onMovementEnded: {
            if (visibleArea.yPosition < 0.01) {
                console.log("loading additional at top",offsetTop)
                vk.getMessages(id, isChat, offsetTop, 20)
            }
            if (visibleArea.yPosition + visibleArea.heightRatio > 0.99 && offsetBottom > 0) {
                console.log("loading additional at bottom",offsetBottom)
                vk.getMessages(id, isChat, Math.max(offsetBottom - 20, 0), Math.min(offsetBottom, 20))
            }
        }
        delegate: MessageComponent{} /*Component {
            Loader {
                source: actionMessages === "" ?
                            "MessageComponent.qml" :
                            "MessageComponentAction.qml"
            }
        }*/

        verticalLayoutDirection: ListView.BottomToTop
        VerticalScrollDecorator {}
    }

    Component.onCompleted: {
        vk.getMessages(id, isChat, -1, 20)
    }

    BusyIndicator {
        anchors.centerIn: parent
        running: !ready
        size: BusyIndicatorSize.Large
    }
}
