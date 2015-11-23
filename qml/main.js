
var handlers = {
    "dialogs": requestDialogs,
    "messages" : requestMessages,
}


function findPage(identificator) {
    var page = pageStack.currentPage
    for (var i=0;i<pageStack.depth;i++) {
        if (page.objectName === identificator) {
            return page
        }
        page = pageStack.previousPage(page)
    }
}

function findMessagesPage() {
    return findPage("messagesPage")
}

function findMessagesModel() {
    var page = findMessagesPage()
    if (page) {
        return page.messagesListModel
    }
}

function findDialogPage() {
    return findPage("dialogsPage")
}

function findDialogModel() {
    var page = findDialogPage()
    if (page) {
        return page.dialogsListModelAlias
    }
}

function requestMessages(data) {
    var page = findMessagesPage()
    if (!page) {
        console.log("ERROR: cannot find message page")
        return
    }

    console.log("appending messages to existing model")

    page.listAlias.model.appendMessages(vk.getStorage(), page.id, page.downloadCount)


    /*if (page.offsetTop === -1 && page.offsetBottom === -1 && data.unreadCount() > 0) {
        page.listAlias.positionViewAtIndex(Math.min(data.unreadCount(), 20), ListView.Contain)
    } else if (page.listAlias.visibleArea.yPosition > 0.99 && page.offsetBottom === -1) {
        page.listAlias.positionViewAtEnd()
    }*/

    if (page.offsetBottom > data.offset()  || page.offsetBottom === -1) {
        page.offsetBottom = data.offset();
    }
    if (page.offsetTop < data.offset() + data.count() || page.offsetTop === -1) {
        page.offsetTop = data.offset() + data.count()
    }

    page.ready = true

}

function requestDialogs(data) {
    var page = findDialogPage()
    if (!page) {
        console.log("ERROR: cannot find dialog page")
        return
    }


    console.log("appending dialogs to a existing model")

    if (page.listAlias.model.count() === 0) {
        page.listAlias.model.appendDialogs(vk.getStorage(), page.downloadCount)
    }
    page.ready = true
}

function requestData(handler, name) {
    if (handlers[name] === undefined) {
        console.log("cannot find function for handler with name",name)
        return;
    }

    handlers[name](handler)
}
