import QtQuick 2.0
import Sailfish.Silica 1.0
import "../handlers.js" as Handlers

TextField {
    id: messageField
    property var forward : []
    property var attachments : []
    property int userId
    property bool chat

    function addForward(id) {
        forward.push(id)
    }
    function getForward() {
        return forward.join(",")
    }

    function getAttachments() {
        return ""
    }

    placeholderText: qsTr("Hi")
    placeholderColor: Theme.secondaryHighlightColor

    EnterKey.enabled: text.length > 0
    EnterKey.highlighted: true
    EnterKey.text: qsTr("Send")

    Keys.onReturnPressed: {
        console.log("send", text)
        var fwd = getForward()
        var attch = getAttachments()
        vk.sendMessage(vk.guid, userId, chat, text, fwd, attch)
        Handlers.showFakeMessage(id, vk.guid, text, forward, attachments)
        vk.guid = vk.guid + 1
        text = ""
    }
}

