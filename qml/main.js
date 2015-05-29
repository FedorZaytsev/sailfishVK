
var defaultAvatar = "http:\/\/vk.com\/images\/camera_100.gif"
var handlers = {
    "dialogs" : processDialogs,
    "messages" : processMessages,
    "longPollServer" : processLongPollServer,
    "userInfoForMessages" : processMessagesFull,
    "friends" : processFriends,
    "iconsForUserUpdate" : processUpdateIcons,
    "additionalUpdateInfo" : processAdditionalUpdateInfo,
};

function processReply(identificator, reply, additional) {
    if (!handlers[identificator]) {
        console.log("processReply ERROR",identificator)
        return
    }

    console.log("got reply",identificator)
    handlers[identificator](reply,additional)
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

function getById(users, id) {
    console.assert(users)
    if (users.length && typeof(users[0].id) !== typeof(id)) {
        console.assert(false)
    }

    for (var i=0;i<users.length;i++) {
        if (users[i].id === id) {
            return users[i]
        }
    }
    console.log("ASSERT")
    console.assert(false)
}

function parseFwdMessages(messages, users) {
    var result = [];
    if (!messages) return result;
    for (var i=0;i<messages.length;i++) {
        var message = messages[i]
        var user = getById(users,message.user_id)
        var fwdMessages = parseFwdMessages(message.fwd_messages, users)
        result.push({
                        userName: user.first_name + " " + user.last_name,
                        date: convertDate(message.date),
                        msg: message.body,
                        //incoming: true,
                        icon: user.photo_50,
                        user_id: message.user_id,
                        fwdMessages: fwdMessages,
                    })

    }
    return result
}

function setToString(ids) {
    var arr = []
    for (var property in ids) {
        arr.push(property)
    }
    return arr.join(",")
}

function getUserName(user) {
    return user.first_name + " " + user.last_name
}

function getAllIds(fwd, ids) {
    if (!fwd) return;
    for (var i=0;i<fwd.length;i++) {
        var item = fwd[i]
        if (item.user_id) {
            ids[item.user_id] = true
            //console.log("found id")
        }
        getAllIds(fwd.fwd_messages)
    }
}

function processMessages(reply) {
    var ids = {}
    for (var i=0;i<reply.items.length;i++) {
        var item = reply.items[i]
        if (item.user_id) {
            ids[item.user_id] = true
        }
        if (item.from_id) {
            ids[item.from_id] = true
        }
        getAllIds(item.fwd_messages,ids)
    }
    var idsStr = setToString(ids)

    console.log("processMessages",idsStr)

    vk.getUserInformation("userInfoForMessages",JSON.stringify(reply),idsStr,"photo_50")
}

function debugPrintTable(t,sep) {
    if (!sep) sep=""
    console.log(sep,"{")
    sep += "    "
    for (var p in t) {
        if (typeof t[p] === "object") {
            console.log(sep,p,":")
            debugPrintTable(t[p],sep)
        } else {
            console.log(sep,p,t[p])
        }
    }
    console.log(sep,"}")
}

function parseAttachments(attachments) {
    var result = {photo:[],}
    if (!attachments) return result;
    for (var i=0;i<attachments.length;i++) {
        if (attachments[i].type === "photo") {
            var item = attachments[i].photo
            var image = item.photo_75
            if (item.photo_604) {
                console.log("size 604")
                image = item.photo_604
            } else if (item.photo_130) {
                console.log("size 130")
                image = item.photo_130
            }
            console.log("image",image)

            result["photo"].push({
                id: item.id,
                image: image
            })
        }
    }
    return result
}


function sortDataByTime(data) {
    return data.sort(function(a,b) {
        if (a[0] === 4 && b[0] === 4) {
            return a[4] - b[4];
        } else {
            return 0;
        }})
}

function parseUpdateFlags(flags) {
    return {
        unread :    (flags & 1) !== 0,
        outbox :    (flags & 2) !== 0,
        replied :   (flags & 4) !== 0,
        important : (flags & 8) !== 0,
        chat :      (flags & 16) !== 0,
        friends :   (flags & 32) !== 0,
        spam :      (flags & 64) !== 0,
        deleted :   (flags & 128) !== 0,
        fixed :     (flags & 256) !== 0,
        media :     (flags & 512) !== 0,
    }
}

function processUpdateIcons(response,additional) {
    console.log("processUpdateIcons",response.length, additional)

    var updateData = JSON.parse(additional)
    for (var i=0;i<updateData.update.length;i++) {
        var item = updateData.update[i]
        console.log("got update",item[0])
        if (item[0] === 4) {    //New message
            var id = item[1]
            var flags = parseUpdateFlags(item[2])
            var fromId = item[3]
            if (fromId > 2000000000) {      //chat?
                fromId = fromId - 2000000000
            }

            var time = item[4]
            var subject = item[5]
            var text = item[6]
            var attachments = item[7]
            var user = getById(response,attachments.from? attachments.from : fromId)

            if (pageStack.currentPage.dialogsListModelAlias) {
                model = pageStack.currentPage.dialogsListModelAlias
                for (var idx=0;idx<model.count;idx++) {
                    console.log(typeof model.get(idx).id, typeof fromId)
                    if (model.get(idx).id === fromId) {
                        console.log("found")
                        model.setProperty(idx,"authorAvatar50",user.photo_50)
                        model.setProperty(idx,"msgId",id)
                        model.setProperty(idx,"msgText",text)
                        model.move(idx,0,1)
                        break
                    }
                }
            } else if (pageStack.currentPage.messagesListModel) {
                model = pageStack.currentPage.messagesListModel
                //var msg = getById()
                var test = ({
                                                                   msg: text,
                                                                   date: convertDate(time),
                                                                   userName: getUserName(user),
                                                                   icon: user.photo_50,
                                                                   incoming: !flags.outbox,
                                                                   repeaterModel: fwdMessages,
                                                                   attachments: attachments
                                                               })
                model.append({})
            }
        }
    }
    var request = JSON.parse(additional)
    vk.subscribeLongPollServer("longPollServer",JSON.stringify(request.additional), request.additional.key, request.additional.server, request.update.ts)
}

//response - users + fwd
//additional - update + additional
function processAdditionalUpdateInfo(response, additional) {
    console.log("processAdditionalUpdateInfo",JSON.stringify(response),"\n\n",additional)

    var model
    var updateData = JSON.parse(additional)
    for (var i=0;i<updateData.update.updates.length;i++) {
        var item = updateData.update.updates[i]
        console.log("got update",item[0], JSON.stringify(item))
        if (item[0] === 4) {    //New message
            var id = item[1]
            var flags = parseUpdateFlags(item[2])
            var fromId = item[3]
            if (fromId > 2000000000) {      //chat?
                fromId = fromId - 2000000000
            }

            var time = item[4]
            var subject = item[5]
            var text = item[6]
            var attachments = item[7]
            var user = getById(response.users,attachments.from? parseInt(attachments.from) : fromId)

            if (pageStack.currentPage.dialogsListModelAlias) {
                model = pageStack.currentPage.dialogsListModelAlias
                for (var idx=0;idx<model.count;idx++) {
                    //console.log(typeof model.get(idx).id, typeof fromId)
                    if (model.get(idx).id === fromId) {
                        console.log("found")
                        model.setProperty(idx,"authorAvatar50",user.photo_50)
                        model.setProperty(idx,"msgId",id)
                        model.setProperty(idx,"msgText",text)
                        model.move(idx,0,1)
                        break
                    }
                }
            } else if (pageStack.currentPage.messagesListModel) {
                model = pageStack.currentPage.messagesListModel
                var msgList = pageStack.currentPage.messagesList


                var msg = getById(response.fwd.items,id)
                var fwdMessages = parseFwdMessages(msg.fwd_messages, response.users)
                var msgAttachments = parseAttachments(item.attachments)
                //console.log("Full message got",JSON.stringify(msg))

                model.append({
                                                                   msg: text,
                                                                   date: convertDate(time),
                                                                   userName: getUserName(user),
                                                                   icon: user.photo_50,
                                                                   incoming: !flags.outbox,
                                                                   repeaterModel: fwdMessages,
                                                                   attachments: msgAttachments
                                                               })
                if (msgList.visibleArea.yPosition + msgList.visibleArea.heightRatio > 0.99) {
                    msgList.positionViewAtEnd()
                }
            }
        }
    }
    var request = JSON.parse(additional)
    vk.subscribeLongPollServer("longPollServer",JSON.stringify(request.additional), request.additional.key, request.additional.server, request.update.ts)


}

//parses structures like
// 1_2:(3_4:(5_6,7_8))
function parseUpdateFwd(s) {
    console.log("parseUpdateFwd",s)
    var result = []
    var begin = 0

    if (!s) return result

    //parses structures like (1_2,3_4,5_6)
    function parseUpdateMessagePair(el) {
        console.log("parseUpdateMessagePair",el)
        return el.split("_")
    }

    for (var i=0;i<s.length;i++) {
        var t
        if (s[i] === ":") {
            console.log("found : at position i =",i,"begin =",begin)
            var k = parseUpdateMessagePair(s.substring(begin,i))
            var v = parseUpdateFwd(s.substring(i+2))
            result.push({message:{userId:k[0], msdId:k[1]}, fwd: v[0]})
            i += v[1] + 2
            begin = i
            console.log("returned, i=",i,s.substring(i))
        } else if (s[i] === ")") {
            console.log("found ) at position i =",i,"begin =",begin)
            if (i-1 != begin) {
                t = parseUpdateMessagePair(s.substring(begin,i))
                result.push({message:{userId:t[0], msgId:t[1]}})
            }
            console.log("result",JSON.stringify(result))
            return [result, i]
        } else if (s[i] === ",") {
            console.log("found , at position i =",i,"begin =",begin)
            if (i-1 !== begin) {
                t = parseUpdateMessagePair(s.substring(begin,i))
                result.push({message:{userId:t[0], msgId:t[1]}})
            }
            begin = i+1
        }
    }
    var pair = parseUpdateMessagePair(s.substring(begin,s.length))
    if (pair.length === 2) {
        result.push({message:{userId:pair[0], msgId:pair[1]}})
    }
    console.log("parseUpdateFwd",JSON.stringify(result))
    return result
}

//returns all user ids from all messages (also forwarded) and message ids from top level
function processUpdateFwd(data,level) {
    var result = []
    if (!data) {
        return result
    }

    for (var i=0;i<data.length;i++) {

        result.push(parseInt(data[i].message.userId))
        result.concat(processUpdateFwd(data[i].fwd))
    }
    return result
}

function processLongPollServer(response, additional) {
    var userIds = []
    var fwdMessageIds = []
    for (var i=0;i<response.updates.length;i++) {
        var item = response.updates[i]
        if (item[0]===4) {                      //MessageAdd
            var id = item[1]
            var fromId = item[3]
            var attachments = item[7]
            if (attachments.from) {
                fromId = attachments.from
            }

            userIds.push(fromId)

            var parsedFwd = parseUpdateFwd(attachments.fwd)
            console.log("got parsedFwdMessages",JSON.stringify(parsedFwd))
            userIds = userIds.concat(parsedFwd)
            fwdMessageIds.push(id)
        }
    }
    if (userIds.length || fwdMessageIds.length) {
        console.log(JSON.stringify(userIds),JSON.stringify(fwdMessageIds),userIds.join(","), fwdMessageIds.join(","))
        vk.getLongPollMessageInformation("additionalUpdateInfo", JSON.stringify({update:response,additional:JSON.parse(additional)}), userIds.join(","), fwdMessageIds.join(","))
    } else {
        processReply("additionalUpdateInfo", [], JSON.stringify({update:response,additional:JSON.parse(additional)}))
    }
}


function processMessagesFull(userInfos, additional) {
    var messages = JSON.parse(additional)
    pageStack.currentPage.offset += 20

    for (var i=messages.items.length-1;i>=0;i--) {
        var item = messages.items[i]

        var user_id = item.from_id?item.from_id:item.user_id
        var user = getById(userInfos,user_id)
        var icon = user.photo_50
        var userName = user.first_name + " " + user.last_name
        var text = item.body
        var date = convertDate(item.date)
        var incoming = item.out === 0
        var isChat = item.chat_id !== undefined
        var fwdMessages = parseFwdMessages(item.fwd_messages, userInfos)
        var attachments = parseAttachments(item.attachments)

        var test = ({
                                                           msg: text,
                                                           date: date,
                                                           userName: userName,
                                                           icon: icon,
                                                           incoming: incoming,
                                                           repeaterModel: fwdMessages,
                                                           attachments: attachments
                                                       })

        pageStack.currentPage.messagesListModel.append(test)
        if (i === 0) {
            vk.setLastMessageId(item.id)
        }
    }
    pageStack.currentPage.messagesList.positionViewAtEnd()
}


function processDialogs(reply) {
    console.log("process dialogs")
    pageStack.currentPage.offset += 20
    var ourUser = reply.user
    for (var i=0;i<reply.dialogs.length;i++) {
        var item = reply.dialogs[i].item
        var users = reply.dialogs[i].user

        var icon = ""
        var fourIcons = ["","","",""]
        var chatName = "chatName"
        var text = item.message.body
        if (item.message.fwd_messages && item.message.fwd_messages.length) {
            text = "Messages"
        }

        var inclomingMsg = item.message.out === 0
        var authorIcon50 = ""
        var isChar
        var msgId = item.message.id
        var identificator = 0

        if (item.message.chat_id) {
            if (item.message.photo_100) {
                icon = item.message.photo_100
            } else if (item.message.users_count === undefined){
                icon = defaultAvatar
            } else if (users.length === 1){
                icon = users[0] ? users[0].photo_100 : ""
            } else {
                fourIcons[0] = users[0] ? users[0].photo_100 : ""
                fourIcons[1] = users[1] ? users[1].photo_100 : ""
                fourIcons[2] = users[2] ? users[2].photo_100 : ""
                fourIcons[3] = users[3] ? users[3].photo_100 : ""
            }

            chatName = item.message.title
            authorIcon50 = getById(users,item.message.user_id).photo_100
            isChar = true
            identificator = item.message.chat_id
        } else {
            var user = users[0]
            icon = user.photo_100
            chatName = user.first_name + " " + user.last_name
            if (!inclomingMsg) {
                authorIcon50 = ourUser.photo_50
            }
            isChar = false
            identificator = item.message.user_id
        }

        pageStack.currentPage.dialogsListModelAlias.append({
                                                                 photo100: icon,
                                                                 name: chatName,
                                                                 msgText: text,
                                                                 isIncoming: inclomingMsg,
                                                                 authorAvatar50: authorIcon50,
                                                                 isChat: isChar,
                                                                 id: identificator,
                                                                 msgId: msgId,
                                                                 iconFour1: fourIcons[0],
                                                                 iconFour2: fourIcons[1],
                                                                 iconFour3: fourIcons[2],
                                                                 iconFour4: fourIcons[3],
                                                             })
        if (i === 0) {
            vk.setLastMessageId(item.id)
        }
    }
    console.log("subscribeLongPollServer")
    vk.subscribeLongPollServer("longPollServer",
                               JSON.stringify({"key":reply.longPoll.key,"server":reply.longPoll.server}), //save
                               reply.longPoll.key,
                               reply.longPoll.server,
                               reply.longPoll.ts)
}


function processFriends(reply) {
    for (var i=0;i<reply.items.length;i++) {
        var item = reply.items[i]
        pageStack.currentPage.friendsListModelAlias.append({
                                                          user_id: item.id,
                                                          name: item.first_name + " " + item.last_name,
                                                          icon: item.photo_100,
                                                          isOnline: item.online,
                                                      })
    }
}
