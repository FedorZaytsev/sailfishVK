import QtQuick 2.0
import Sailfish.Silica 1.0
import "../main.js" as Main

Page {
    id: friendsPage
    property alias friendsListModelAlias : friendsListModel

    SilicaListView {
        id: friendsList
        anchors.fill: parent

        PullDownMenu {
            MenuItem {
                text: "1"
                onClicked: {

                }
            }
        }
        ListModel {
            id: friendsListModel
        }
        model: friendsListModel
        spacing: Theme.paddingLarge
        header: PageHeader {
            title: "Friends"
        }
        delegate: FriendComponent{}
        VerticalScrollDecorator {}
    }
    Component.onCompleted: {
        vk.getFriends("friends",0)
    }

}
