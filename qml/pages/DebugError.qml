import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.vk.VK 1.0

Page {
    id: page
    property string msg
    property int type
    Column {
        anchors.fill: parent
        spacing: (Screen.height - ooopsLabel.height - msgLabel.height - hintLabel.height - button.height)/5
        Component.onCompleted: console.log("Column",spacing)
        Label {
            id: ooopsLabel
            width: Screen.width
            font.bold: true
            font.pixelSize: Theme.fontSizeLarge
            horizontalAlignment: Text.AlignHCenter
            text: "Ooops\nError!"
        }

        Label {
            id: msgLabel
            x: Screen.width*0.1
            width: Screen.width*0.8
            wrapMode: Text.Wrap
            font.pixelSize: Theme.fontSizeMedium
            horizontalAlignment: Text.AlignHCenter
            text: msg
        }
        Label {
            id: hintLabel
            width: Screen.width
            font.pixelSize: Theme.fontSizeLarge
            horizontalAlignment: Text.AlignHCenter
            text: {
                if (type === VK.ERROR_HANDLER_RESTART) {
                    return "Please restart application";
                } else if (type === VK.ERROR_HANDLER_RELOGIN) {
                    vk.dropAuthorization()
                    return "Please restart application and relogin";
                } else {
                    return "This is not a fatal error";
                }
            }
        }

        Button {
            id:emailButton
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Send bug report")
            onClicked: {
                var emailPage = Qt.createQmlObject("
import QtQuick 2.0;
import Sailfish.Email 1.1;
EmailComposerPage {
    emailTo:\"best.zaytsev@gmail.com\";
    emailSubject: \"SailVK version"+vk.appVersion()+"\";
    emailBody: \"-----------ATTENTION!---------\nLogs may contains some personal information such as messages and account details. Logs do not contains your login/password.\n\n\";
    Component.onCompleted: {
        attachmentsModel.append({\"url\": \"file://"+vk.getLogPath()+"\", \"title\": \""+vk.getLogName()+"\", \"mimeType\": \""+vk.getLogName()+"\"})
    }

}", applicationWindow)
                pageStack.push(emailPage)
            }
        }

        Button {
            id: button
            anchors.horizontalCenter: parent.horizontalCenter
            text: {
                if (type === VK.ERROR_HANDLER_RESTART || type === VK.ERROR_HANDLER_RELOGIN) {
                    return "Exit";
                } else {
                    return "Back";
                }
            }
            onClicked: {
                if (type === VK.ERROR_HANDLER_RESTART || type === VK.ERROR_HANDLER_RELOGIN) {
                    Qt.quit()
                } else {
                    pageStack.navigateBack()
                }
            }
        }
    }
}
