var handlers = {
    "dialogs" : handlerDialogs,
    "longPollServer" : handlerLongPoll,
    "messages" : handlerMessages,
}


var longPollHandlers = {}
function fullLPHandlers() {
    if (typeof VKLPEventType !== "undefined") {
        longPollHandlers[VKLPEventType.MESSAGE_DELETE] = processMessageDelete
        longPollHandlers[VKLPEventType.MESSAGE_FLAGS_CHANGE] = processMessageFlagsChange
        longPollHandlers[VKLPEventType.MESSAGE_FLAGS_SET] = processMessageFlagsSet
        longPollHandlers[VKLPEventType.MESSAGE_FLAGS_RESET] = processMessageFlagsReset
        longPollHandlers[VKLPEventType.MESSAGE_NEW] = processMessageNew
        longPollHandlers[VKLPEventType.MESSAGE_MARK_READ_INCOMING] = processMessageMarkReadIncoming
        longPollHandlers[VKLPEventType.MESSAGE_MARK_READ_OUTCOMING] = processMessageMarkReadOutcoming
        longPollHandlers[VKLPEventType.USER_ONLINE] = processUserOnline
        longPollHandlers[VKLPEventType.USER_OFFLINE] = processUserOffline
        longPollHandlers[VKLPEventType.CHAT_UPDATED] = processChatUpdated
        longPollHandlers[VKLPEventType.USER_TYPING] = processTyping
        longPollHandlers[VKLPEventType.CHAT_USER_TYPING] = processTyping
        longPollHandlers[VKLPEventType.VIDEOCALL] = processVideocall
        longPollHandlers[VKLPEventType.COUNTER_UPDATE] = processCounterUpdate
    }
}

function printObject(obj) {
    for (var prop in obj) {
        console.log(prop, typeof obj[prop], obj[prop])
    }
}

function ready(name, data) {
    console.log("ready",name)
    console.assert(handlers[name])

    handlers[name](data)
}

function findMessagesPage() {
    var page = pageStack.currentPage
    for (var i=0;i<pageStack.depth;i++) {
        if (page.messagesListModel) {
            return page
        }
        page = pageStack.previousPage(page)
    }
}

function findMessagesModel() {
    var page = findMessagesPage()
    if (page) {
        return page.messagesListModel
    }
}

function findDialogPage() {
    var page = pageStack.currentPage
    for (var i=0;i<pageStack.depth;i++) {
        if (page.dialogsListModelAlias) {
            return page
        }
        page = pageStack.previousPage(page)
    }
    console.log("nothing found")
}

function findDialogModel() {
    var page = findDialogPage()
    if (page) {
        return page.dialogsListModelAlias
    }
}

function prepareAttachments(e) {

    function parsePhoto(result, el) {
        var t = {
                    id: el.id(),
                    image: el.maxSuitablePhoto(),
                    imageSize: el.maxSuitableSize()
        }
        if (result.photo) {
            result.photo.push(t)
        } else {
            result.photo = [t]
        }
    }
    function parseVideo(result, el) {
        var t = {
            id: el.id(),
            name: el.title(),
            url: el.playerUrl()
        }
        if (result.video) {
            result.video.push(t)
        } else {
            result.video = [t]
        }
    }
    var funcs = {}
    funcs[VKContainerAttachments.PHOTO] = parsePhoto
    funcs[VKContainerAttachments.VIDEO] = parseVideo

    var result = {
        /*photo: [],
        audio: [],
        video: [],
        wall: [],
        wall_reply: [],
        sticker: [],
        doc: [],*/
    }
    if (e) {
        for (var type in funcs) {
            for (var i=0;i<e.count(type);i++) {
                var el = e.get(type, i)
                funcs[type](result, el)
            }
        }
    }
    return result
}

function addMessage(model, element, offset, incoming, position) {

    if (offset === undefined) {
        offset = 0
    }

    if (incoming === undefined) {
        incoming = element.isIncoming()
    }


    var t = {
        id: element.msgId(),
        msg: element.body(),
        date: convertDate(element.date()),
        userName: element.user().firstName() + " " + element.user().lastName(),
        icon: element.user().iconSmall(),
        incoming: incoming,
        offset: offset,
        highlight: false,
        isRead: element.readState(),
        attachments: prepareAttachments(element.attachments()),
        chatId: element.chatId(),
    }
    if (position === undefined) {
        model.append(t)
    } else {
        model.insert(position, t)
    }

    for (var i=0;i<element.countFwd();i++) {
        addMessage(model, element.getFwd(i), offset + 1, incoming, position !== undefined? position + 1 : position)
    }
}

function processMsg(msg) {
    if (msg.body() === "" && msg.attachments()) {
        var desc = msg.attachments().description()
        if (desc.length > 0) {
            return desc.charAt(0).toUpperCase() + desc.slice(1)
        }
    }
    return msg.body()
}

function addDialog(model, dialog, position, additionalUnreadCount) {
    if (!model) return

    var message = dialog.message()
    var icon = dialog.chatIcon()

    if ((additionalUnreadCount + (message.isIncoming() ? dialog.unreadCount() : 0)) < 0) console.assert(0,"ggg4")
    var t = {
        name: dialog.chatName(),
        msgText: processMsg(message),
        isIncoming: message.isIncoming(),
        authorAvatar50: message.user().iconSmall(),
        isChat: dialog.isChat(),
        id: dialog.chatId(),
        msgId: message.msgId(),
        iconFour1: icon.get(0) || "",
        iconFour2: icon.get(1) || "",
        iconFour3: icon.get(2) || "",
        iconFour4: icon.get(3) || "",
        isRead: message.readState(),
        unreadCount: additionalUnreadCount + (message.isIncoming() ? dialog.unreadCount() : 0),
    }

    if (position !== undefined) {
        model.insert(position, t)
    } else {
        model.append(t)
    }
}

function updateDialog(model, dialog, pos) {
    if (!model) return

    var message = dialog.message()

    console.log("unreadCount",message.msgId(), model.get(0).unreadCount, model.get(0).unreadCount + (message.isIncoming() ? 1 : 0))

    model.move(pos, 0, 1)
    model.setProperty(0, "name", dialog.chatName())
    model.setProperty(0, "msgText", processMsg(message))
    model.setProperty(0, "isIncoming", message.isIncoming())
    model.setProperty(0, "authorAvatar50", message.user().iconSmall())
    model.setProperty(0, "msgId", message.msgId())
    model.setProperty(0, "isRead", message.readState())
    model.setProperty(0, "unreadCount", model.get(0).unreadCount + (message.isIncoming() ? 1 : 0))

}

function normalizeTime(param) {
    console.assert(param>=0)
    if (param > 9) {
        return ""+param
    } else {
        return "0"+param
    }
}

function convertDate(unixtime) {
    var date = new Date(unixtime * 1000);
    var hours = ""+date.getHours()
    var minutes = normalizeTime(date.getMinutes())
    var day = normalizeTime(date.getDate())
    var month = normalizeTime(date.getMonth()+1)
    var year = normalizeTime(date.getFullYear())
    return hours+":"+minutes+", "+day+"."+month+"."+year
}

function getFwd(data) {
    var result = []
    for (var i=0;i<data.countFwd();i++) {
        var el = data.getFwd(i)
        var fwd = getFwd(el)
        result.push({
                        userName: el.user().firstName() + " " + el.user().lastName(),
                        date: convertDate(el.date()),
                        msg: el.body(),
                        icon: el.user().iconSmall(),
                        user_id: 0,
                        fwdMessages: fwd,
                        attachments: {photo: []},
        })
    }
    return result
}

function handlerMessages(data) {
    console.log("handlerMessages", data.count())
    var model = findMessagesModel()
    if (!model) {
        console.log("POSIBLE ERROR: NO pageStack.currentPage.messagesListModel")
        return
    }

    for (var i=data.count()-1;i>=0;i--) {
        var element = data.get(i)

        addMessage(model, element)
    }
    pageStack.currentPage.messagesList.positionViewAtEnd()
}


function findMsgId(model, id) {
    if (model) {
        for (var i=0;i<model.count;i++) {
            var e = model.get(i)
            if (e.id === id) {
                return i
            }
        }
    }
}

function deleteMessage(msgId, chatId, prev) {

    var mmodel = findMessagesModel()
    var dmodel = findDialogModel()
    var msgIdMessages = findMsgId(mmodel, msgId)
    var msgIdDialogs = findMsgId(dmodel, chatId)

    //
    var countUpdated = false;
    if (msgIdMessages !== undefined) {
        if (!mmodel.get(msgIdMessages).isRead && msgIdDialogs !== undefined) {
            if (dmodel.get(msgIdDialogs).unreadCount <= 0) console.assert(0,"ggg1")
            dmodel.setProperty(msgIdDialogs, "unreadCount", dmodel.get(msgIdDialogs).unreadCount - 1)
            countUpdated = true;
        }

        //count how many messages delete
        var count
        for (count = 1;msgIdMessages + count < mmodel.count; count++) {
            if (mmodel.get(msgIdMessages + count).offset === 0) {
                break
            }
        }

        mmodel.remove(msgIdMessages, count)

    }

    //updating unread count
    if (msgIdMessages === undefined && msgIdDialogs !== undefined && !dmodel.get(msgIdDialogs).isRead && !countUpdated) {
        if (dmodel.get(msgIdDialogs).unreadCount <= 0) console.assert(0,"ggg2")
        dmodel.setProperty(msgIdDialogs, "unreadCount", dmodel.get(msgIdDialogs).unreadCount - 1)
    }

    //updating message in dialog view
    if (msgIdDialogs !== undefined && prev) {
        dmodel.setProperty(id, "msgText", processMsg(prev))
        dmodel.setProperty(id, "isRead", prev.readState())
        dmodel.setProperty(id, "msgId", prev.msgId())
        dmodel.setProperty(id, "isIncoming", prev.isIncoming())
        dmodel.setProperty(id, "authorAvatar50", prev.user().iconSmall())
    }
}

function restoreMessage(msg) {
    var el = msg
    var mmodel = findMessagesModel()
    var dmodel = findDialogModel()
    var id = findMsgId(dmodel, el.chatId())

    if (dmodel && id !== undefined && el.msgId() > dmodel.get(id).msgId) {
        dmodel.setProperty(id, "msgText", processMsg(el))
        dmodel.setProperty(id, "isRead", el.readState())
        dmodel.setProperty(id, "msgId", el.msgId())
        dmodel.setProperty(id, "isIncoming", el.isIncoming())
        dmodel.setProperty(id, "authorAvatar50", el.user().iconSmall())
    }

    var messages = findMessagesPage()
    if (messages && messages.id === el.chatId()) {
        if (mmodel.get(mmodel.count-1).id < el.msgId()) {
            //iterating over all messages and find where we must place restored msg
            var idx
            for (idx=mmodel.count-1;idx>=0;idx--) {
                var modelElement = mmodel.get(idx)
                if (modelElement.offset === 0 && modelElement.id < el.msgId()) {

                    for (idx++;idx<mmodel.count && mmodel.get(idx).offset !== 0;idx++) {}

                    console.log("found place for restored msg: idx =",idx)
                    break
                }
            }
            addMessage(mmodel, el, undefined, undefined, idx)
        }
    }
}

function processMessageFlagsChange(el) {
    var id = el.id()
    var chatId = el.userId()
    var flags = el.flags()
    var mmodel = findMessagesModel()
    var dmodel = findDialogModel()
    var msgIdMessages = findMsgId(mmodel, id)
    var msgIdDialogs = findMsgId(dmodel, chatId)

    console.assert(false)
    console.log("msgIdMessages",msgIdMessages,"msgIdDialogs",msgIdDialogs)
    console.log("flags")
    el.flags().print()

    if (msgIdMessages) {
        mmodel.setProperty(msgIdMessages, "isRead", flags.isSet(VKLPFlags.UNREAD))
        mmodel.setProperty(msgIdMessages, "incoming", !flags.isSet(VKLPFlags.OUTBOX))
        mmodel.setProperty(msgIdMessages, "isChat", flags.isSet(VKLPFlags.CHAT))
        if (flags.isSet(VKLPFlags.DELETED)) {
            //TODO
        }
    }
    if (msgIdDialogs) {
        dmodel.setProperty(msgIdDialogs, "incoming", !flags.isSet(VKLPFlags.OUTBOX))
        dmodel.setProperty(msgIdDialogs, "isChat", flags.isSet(VKLPFlags.CHAT))
    }

}

function processMessageFlagsSet(el) {
    var flags = el.flags()
    var id = el.id()
    var chatId = el.userId()
    var msg = el.message()
    console.log("processMessageFlagsSet", msg)
    flags.print()

    var mmodel = findMessagesModel()
    var dmodel = findDialogModel()
    var msgIdMessages = findMsgId(mmodel, id)
    var msgIdDialogs = findMsgId(dmodel, chatId)

    if (flags.isSet(VKLPFlags.DELETED)) {
        //todo
        deleteMessage(id, chatId, msg)
    }
    if (flags.isSet(VKLPFlags.UNREAD)) {
        if (msgIdMessages !== undefined) {
            mmodel.setProperty(msgIdMessages, "isRead", flags.isSet(VKLPFlags.UNREAD))
        }
        if (msgIdDialogs !== undefined) {
            dmodel.setProperty(msgIdDialogs, "unreadCount", dmodel.get(msgIdDialogs).unreadCount + 1)
        }
    }

}

function processMessageFlagsReset(el) {
    var flags = el.flags()
    console.log("processMessageFlagsReset")
    flags.print()

    var mmodel = findMessagesModel()
    var dmodel = findDialogModel()
    var msgIdMessages = findMsgId(mmodel, el.id())
    var msgIdDialogs = findMsgId(dmodel, el.userId())

    if (flags.isSet(VKLPFlags.DELETED)) {
        restoreMessage(el.message())
    }

    if (flags.isSet(VKLPFlags.UNREAD)) {

        if (msgIdMessages !== undefined) {
            mmodel.setProperty(msgIdMessages, "isRead", !flags.isSet(VKLPFlags.UNREAD))
        }
        if (msgIdDialogs !== undefined) {
            console.log("descrease count",el.id(), el.userId(), dmodel.get(msgIdDialogs).unreadCount)
            if (dmodel.get(msgIdDialogs).unreadCount <= 0) console.log("ggggg")
            dmodel.setProperty(msgIdDialogs, "unreadCount", dmodel.get(msgIdDialogs).unreadCount - 1)
        }
    }
}

function processMessageDelete(el) {
    console.log("processMessageDelete id =",id)

    deleteMessage(el.id(), el.userId(), el.message())
}

function processMessageNew(el) {
    var dmodel = findDialogModel()
    var mmodel = findMessagesModel()
    var mpage = findMessagesPage()
    var dialog = el.dialog()
    var additionalUnreadCount = 0
    var dialogId = findMsgId(dmodel, dialog.chatId())

    console.log("dialogId",dialogId, "chatId", dialog.chatId(), "dmodel.get(dialogId).unreadCount", dmodel.get(dialogId).unreadCount)
    if (dialogId !== undefined) {

        updateDialog(dmodel, dialog, dialogId)
    } else {
        addDialog(dmodel, dialog, 0, additionalUnreadCount)
    }


    console.log("adding element", dialog.message().readState(), additionalUnreadCount)
    if (mpage && dialog.chatId() === mpage.id) {
        addMessage(mmodel, dialog.message())
    }
}

function processUserOnline(el) {
    console.log("nothing done for UserOnline event")
}

function processUserOffline(el) {
    console.log("nothing done for UserOffline event")
}

function processMessageMarkReadIncoming(el) {
    console.log("nothing done for MarkReadIncoming event")
}

function processMessageMarkReadOutcoming(el) {
    console.log("nothing done for MarkReadOutcoming event")
}

function processChatUpdated(el) {
    console.log("nothing done for ChatUpdated event")
}

function processCounterUpdate(el) {
    console.log("nothing done for CounterUpdate event")
}

function processTyping(el) {
    //console.log("nothing done for Typing event")

    console.log("processTyping ",el.userName())

    var mpage = findMessagesPage()
    var dmodel = findDialogModel()
    var dpage = findDialogPage()
    if (mpage && mpage.id === el.chatId()) {
        mpage.messagesList.footerItem.addUser(el.userName())
    }


    var dialogId = findMsgId(dmodel, el.chatId())
    if (dialogId !== undefined) {
        //dpage.dialogListAlias.currentIndex = dialogId
        //dpage.dialogListAlias.currentItem.dialogElementAlias.addUser(el.userName())
    }

}

function processVideocall(el) {
    console.log("nothing done for Videocall event")
}

function handlerLongPoll(data) {
    console.log("handlerPoll",data.count())

    var dmodel = findDialogModel()
    var mmodel = findMessagesModel()
    var mpage = findMessagesPage()

    for (var i=0;i<data.count();i++) {
        var el = data.at(i)
        if (longPollHandlers[el.type()]) {
            console.log("processing event with type",el.type())
            longPollHandlers[el.type()](el)
        } else {
            console.assert(0,"No handler for",el.type())
        }
    }

    data.clean()

    if (mmodel) {
        var list = mpage.messagesList
        console.log("log",list.visibleArea.yPosition, list.visibleArea.heightRatio)
        if (1.0 - (list.visibleArea.yPosition + list.visibleArea.heightRatio) < 0.001) {
            list.positionViewAtEnd()
        }
    }
    console.log("handlerPoll end")
}

function handlerDialogs(data) {
    var mod = findDialogModel()
    if (!mod) return

    pageStack.currentPage.offset += 20
    for (var i=0;i<data.count();i++) {
        var dialog = data.at(i)

        addDialog(mod, dialog, undefined, 0)

    }
}

fullLPHandlers()
