import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    id: delegate
    x: Theme.paddingMedium
    height: 100

    property alias dialogElementAlias : dialogElement

    Loader {
        id: loader
        sourceComponent: unreadCount > 0 ? unreadCountLabel : undefined
    }
    Component {
        id: unreadCountLabel
        Label {
            x: Screen.width - Theme.paddingMedium - width - Theme.paddingMedium
            width: 50
            horizontalAlignment: Text.AlignRight
            text: "<b>" + unreadCount + "</b>"
            color: unreadCount > 0 ? Theme.highlightColor : Theme.primaryColor
        }
    }

    Row {
        id: row
        spacing: Theme.paddingMedium
        DialogIconHolder {
            id: iconHolder
        }

        Column {
            Item {
                width: chatName.width + chatName.height
                height: chatName.height
                Label {
                    id: chatName
                    text: "<b>"+name+"</b>"
                    elide: Text.ElideRight
                    width: Screen.width - 2*delegate.x - row.spacing - iconHolder.width - (loader.item ? loader.item.width : 0)
                    color: unreadCount > 0 ? Theme.highlightColor : Theme.primaryColor
                }
                GlassItem {
                    x: chatName.x + chatName.contentWidth + Theme.paddingMedium
                    height: chatName.height
                    width: chatName.height
                    falloffRadius: 0.2
                    radius: 0.2
                    visible: !isChat && online
                }
            }
            DialogElement {
                id: dialogElement
                offset: iconHolder.width + row.spacing + delegate.x
                needIcon: !isIncoming || isChat
                isHighlighted: unreadCount > 0
            }
        }
    }
    onClicked: {
        pageStack.push(Qt.resolvedUrl("Messages.qml"),{
                           id: id,
                           dialogIndex: index,
                           listHeader: chatName.text,
                           isChat: isChat,
                       })
    }
}
