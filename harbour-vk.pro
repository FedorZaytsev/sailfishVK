# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-vk
QT += sql
QMAKE_CXXFLAGS += -Werror

CONFIG += sailfishapp c++11

SOURCES += src/harbour-vk.cpp \
    src/vk.cpp \
    src/vkpixmapprovider.cpp \
    src/vkstorage.cpp \
    src/vkchatinfo.cpp \
    src/vkhandlerdialogs.cpp \
    src/pendingrequest.cpp \
    src/vkerrors.cpp \
    src/vkcontainerdialog.cpp \
    src/vkcontainermessage.cpp \
    src/vkcontaineruser.cpp \
    src/vkhandlermessages.cpp \
    src/vkhandlerusers.cpp \
    src/vkabstracthandler.cpp \
    src/vkabstractcontainer.cpp \
    src/vklongpollserver.cpp \
    src/vkcontainerchaticon.cpp \
    src/vkqmlnetworkaccessmanagerfactor.cpp \
    src/vknetworkaccessmanager.cpp \
    src/vklongpollupdateparser.cpp \
    src/vklongpollcontainer.cpp \
    src/vkhandlerlongpollupdatedata.cpp \
    src/qmllist.cpp \
    src/vkcontainerattachments.cpp \
    src/vkcontainerphoto.cpp \
    src/vkcontainervideo.cpp \
    src/vkhandlermarkasread.cpp \
    src/qmlnetworkaccessmanagerfactory.cpp \
    src/vkcontaineraudio.cpp \
    src/vkcontainerdocument.cpp \
    src/vklpabstract.cpp \
    src/vklpmessagedelete.cpp \
    src/vkhandlersendmessage.cpp \
    src/vklpmessageflagschange.cpp \
    src/vklpeventtype.cpp \
    src/vklpflags.cpp \
    src/vklpmessageflagsset.cpp \
    src/vklpmessageflagsreset.cpp \
    src/vklpmessagenew.cpp \
    src/vklpmessagemarkincoming.cpp \
    src/vklpmessagemarkoutcoming.cpp \
    src/vklpuseroffline.cpp \
    src/vklpuseronline.cpp \
    src/vklpchatupdated.cpp \
    src/vkcontainermessageaction.cpp \
    src/vklpusertyping.cpp \
    src/vklpchatusertyping.cpp \
    src/vklpvideocall.cpp \
    src/vklpcounterupdate.cpp \
    src/vkusertypinghelper.cpp \
    src/debug.cpp \
    src/vkcontainerwall.cpp \
    src/vkcontainerwallreply.cpp \
    src/vkcontainersticker.cpp \
    src/vkcontainerlink.cpp

OTHER_FILES += qml/harbour-vk.qml \
    qml/cover/CoverPage.qml \
    qml/pages/Auth.qml \
    rpm/harbour-vk.changes.in \
    rpm/harbour-vk.spec \
    rpm/harbour-vk.yaml \
    translations/*.ts \
    harbour-vk.desktop \
    qml/debug.js \
    qml/main.js \
    qml/pages/Dialogs.qml \
    qml/pages/DialogComponent.qml \
    qml/pages/DialogElement.qml \
    qml/pages/Messages.qml \
    qml/pages/Friends.qml \
    qml/pages/DialogIconHolder.qml \
    qml/pages/FriendComponent.qml \
    qml/handlers.js \
    qml/cache.js \
    qml/pages/MessageData.qml \
    qml/pages/MessageComponent.qml \
    qml/pages/DebugHello.qml \
    qml/pages/MessageField.qml \
    qml/pages/MessageFooter.qml \
    qml/pages/ImageFullScreen.qml \
    qml/pages/ImageViewFullScreen.qml \
    qml/pages/MessageMultiImage.qml \
    qml/pages/MessageVideo.qml \
    qml/pages/DebugError.qml \
    qml/pages/InfoPopup.qml \
    qml/pages/MessageAudio.qml \
    qml/pages/MessageWall.qml \
    qml/pages/MessageWallReply.qml \
    qml/pages/MessageSticker.qml \
    qml/pages/MessageLink.qml

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n
TRANSLATIONS += translations/harbour-vk-de.ts
CONFIG += precompile_header
PRECOMPILED_HEADER += src/debug.h
#DEFINES += "VK_DEBUG"


HEADERS += \
    src/vk.h \
    src/vkpixmapprovider.h \
    src/debug.h \
    src/vkstorage.h \
    src/vkchatinfo.h \
    src/vkhandlerdialogs.h \
    src/pendingrequest.h \
    src/vkcontainerdialog.h \
    src/vkcontainermessage.h \
    src/vkcontaineruser.h \
    src/vkhandlermessages.h \
    src/vkhandlerusers.h \
    src/vkabstracthandler.h \
    src/vkabstractcontainer.h \
    src/vklongpollserver.h \
    src/vkcontainerchaticon.h \
    src/vkqmlnetworkaccessmanagerfactor.h \
    src/vknetworkaccessmanager.h \
    src/vklongpollupdateparser.h \
    src/vklongpollcontainer.h \
    src/vkhandlerlongpollupdatedata.h \
    src/qmllist.h \
    src/vkcontainerattachments.h \
    src/vkcontainerphoto.h \
    src/vkcontainervideo.h \
    src/vkhandlermarkasread.h \
    src/qmlnetworkaccessmanagerfactory.h \
    src/vkcontaineraudio.h \
    src/vkcontainerdocument.h \
    src/vklpabstract.h \
    src/vklpmessagedelete.h \
    src/vkhandlersendmessage.h \
    src/vklpmessageflagschange.h \
    src/vklpeventtype.h \
    src/vklpflags.h \
    src/vklpmessageflagsset.h \
    src/vklpmessageflagsreset.h \
    src/vklpmessagenew.h \
    src/vklpmessagemarkincoming.h \
    src/vklpmessagemarkoutcoming.h \
    src/vklpuseroffline.h \
    src/vklpuseronline.h \
    src/vklpchatupdated.h \
    src/vkcontainermessageaction.h \
    src/vklpusertyping.h \
    src/vklpchatusertyping.h \
    src/vklpvideocall.h \
    src/vklpcounterupdate.h \
    src/vkusertypinghelper.h \
    src/vkcontainerwall.h \
    src/vkcontainerwallreply.h \
    src/vkcontainersticker.h \
    src/vkcontainerlink.h

RESOURCES +=

