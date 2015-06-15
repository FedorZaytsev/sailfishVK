

var handlers = {
    "dialogs" : handlerDialogs
}

function printObject(obj) {
    for (var prop in obj) {
        console.log(prop, obj[prop])
    }
}

function ready(name, data) {
    console.log("ready",name)
    console.assert(handlers[name])

    handlers[name](data)
}

function handlerDialogs(data) {
    if (!pageStack.currentPage.pageId !== "dialogs") return;

    pageStack.currentPage.offset += 20
    for (var i=0;i<data.count();i++) {
        console.log(i)
        var dialog = data.at(i)
        var message = dialog.message()
        var icon = dialog.chatIcon()
        console.log("name", dialog.chatName())
        console.log("body", message.body())
        console.log("incoming", message.isIncoming())
        console.log("icon", message.user().iconSmall())
        console.log("is_chat", dialog.isChat())
        console.log("id",dialog.chatId())
        //printObject(message.user())
        pageStack.currentPage.dialogsListModelAlias.append({
                                                                 name: dialog.chatName(),
                                                                 msgText: message.body(),
                                                                 isIncoming: message.isIncoming(),
                                                                 authorAvatar50: message.user().iconSmall(),
                                                                 isChat: dialog.isChat(),
                                                                 id: dialog.chatId(),
                                                                 iconFour1: icon.get(0) || "",
                                                                 iconFour2: icon.get(1) || "",
                                                                 iconFour3: icon.get(2) || "",
                                                                 iconFour4: icon.get(3) || "",
                                                                 unreadCount: dialog.unreadCount(),
                                                             })
    }
}

