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
QMAKE_CXXFLAGS += -Werror -std=c++0x -g -rdynamic -DQT_SHAREDPOINTER_TRACK_POINTERS

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
    src/vkcontainerlink.cpp \
    src/debuglogbuffer.cpp \
    src/vklpunreadcount.cpp \
    src/vknetworkmanager.cpp \
    src/vkhandlerlongpollserverkey.cpp \
    src/vkcontainermessageemoji.cpp \
    src/vkemojiparser.cpp \
    src/vktextwrap.cpp

OTHER_FILES += qml/harbour-vk.qml \
    qml/cover/CoverPage.qml \
    qml/pages/Auth.qml \
    rpm/harbour-vk.changes.in \
    rpm/harbour-vk.spec \
    rpm/harbour-vk.yaml \
    translations/*.ts \
    harbour-vk.desktop \
    qml/pages/Dialogs.qml \
    qml/pages/DialogComponent.qml \
    qml/pages/DialogElement.qml \
    qml/pages/Messages.qml \
    qml/pages/Friends.qml \
    qml/pages/DialogIconHolder.qml \
    qml/pages/FriendComponent.qml \
    qml/handlers.js \
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
    qml/pages/MessageLink.qml \
    qml/pages/MessageDocument.qml \
    qml/pages/LoadingFooter.qml \
    qml/pages/MessageComponentAction.qml \
    qml/emoji/D83DDE0A.png \
    qml/emoji/D83DDE03.png \
    qml/emoji/D83DDE09.png \
    qml/emoji/D83DDE06.png \
    qml/emoji/D83DDE1C.png \
    qml/emoji/D83DDE0B.png \
    qml/emoji/D83DDE0D.png \
    qml/emoji/D83DDE0E.png \
    qml/emoji/D83DDE12.png \
    qml/emoji/D83DDE0F.png \
    qml/emoji/D83DDE14.png \
    qml/emoji/D83DDE22.png \
    qml/emoji/D83DDE2D.png \
    qml/emoji/D83DDE29.png \
    qml/emoji/D83DDE28.png \
    qml/emoji/D83DDE10.png \
    qml/emoji/D83DDE0C.png \
    qml/emoji/D83DDE20.png \
    qml/emoji/D83DDE21.png \
    qml/emoji/D83DDE07.png \
    qml/emoji/D83DDE30.png \
    qml/emoji/D83DDE32.png \
    qml/emoji/D83DDE33.png \
    qml/emoji/D83DDE37.png \
    qml/emoji/D83DDE1A.png \
    qml/emoji/D83DDE08.png \
    qml/emoji/D83DDC4D.png \
    qml/emoji/D83DDC4E.png \
    qml/emoji/D83DDC4C.png \
    qml/emoji/D83DDC0E.png \
    qml/emoji/D83DDC0F.png \
    qml/emoji/D83DDC1C.png \
    qml/emoji/D83DDC2B.png \
    qml/emoji/D83DDC2E.png \
    qml/emoji/D83DDC03.png \
    qml/emoji/D83DDC3B.png \
    qml/emoji/D83DDC3C.png \
    qml/emoji/D83DDC05.png \
    qml/emoji/D83DDC13.png \
    qml/emoji/D83DDC18.png \
    qml/emoji/D83DDC94.png \
    qml/emoji/D83DDCAD.png \
    qml/emoji/D83DDC36.png \
    qml/emoji/D83DDC31.png \
    qml/emoji/D83DDC37.png \
    qml/emoji/D83DDC11.png \
    qml/emoji/D83DDC00.png \
    qml/emoji/D83DDC0C.png \
    qml/emoji/D83DDC1B.png \
    qml/emoji/D83DDC1D.png \
    qml/emoji/D83DDC1F.png \
    qml/emoji/D83DDC2A.png \
    qml/emoji/D83DDC2C.png \
    qml/emoji/D83DDC2D.png \
    qml/emoji/D83DDC3A.png \
    qml/emoji/D83DDC3D.png \
    qml/emoji/D83DDC2F.png \
    qml/emoji/D83DDC5C.png \
    qml/emoji/D83DDC7B.png \
    qml/emoji/D83DDC14.png \
    qml/emoji/D83DDC23.png \
    qml/emoji/D83DDC24.png \
    qml/emoji/D83DDC40.png \
    qml/emoji/D83DDC42.png \
    qml/emoji/D83DDC43.png \
    qml/emoji/D83DDC46.png \
    qml/emoji/D83DDC47.png \
    qml/emoji/D83DDC48.png \
    qml/emoji/D83DDC51.png \
    qml/emoji/D83DDC60.png \
    qml/emoji/D83DDCA1.png \
    qml/emoji/D83DDCA3.png \
    qml/emoji/D83DDCAA.png \
    qml/emoji/D83DDCAC.png \
    qml/emoji/D83DDD14.png \
    qml/emoji/D83DDD25.png \
    qml/emoji/D83CDF1F.png \
    qml/emoji/D83CDF4C.png \
    qml/emoji/D83CDF7A.png \
    qml/emoji/D83CDF7B.png \
    qml/emoji/D83CDF39.png \
    qml/emoji/D83CDF45.png \
    qml/emoji/D83CDF52.png \
    qml/emoji/D83CDF81.png \
    qml/emoji/D83CDF82.png \
    qml/emoji/D83CDF84.png \
    qml/emoji/D83CDFC1.png \
    qml/emoji/D83CDFC6.png \
    qml/emoji/D83CDF3A.png \
    qml/emoji/D83CDF3B.png \
    qml/emoji/D83CDF3C.png \
    qml/emoji/D83CDF3D.png \
    qml/emoji/D83CDF4A.png \
    qml/emoji/D83CDF4B.png \
    qml/emoji/D83CDF4D.png \
    qml/emoji/D83CDF4E.png \
    qml/emoji/D83CDF4F.png \
    qml/emoji/D83CDF6D.png \
    qml/emoji/D83CDF37.png \
    qml/emoji/D83CDF38.png \
    qml/emoji/D83CDF46.png \
    qml/emoji/D83CDF49.png \
    qml/emoji/D83CDF50.png \
    qml/emoji/D83CDF51.png \
    qml/emoji/D83CDF53.png \
    qml/emoji/D83CDF54.png \
    qml/emoji/D83CDF55.png \
    qml/emoji/D83CDF56.png \
    qml/emoji/D83CDF57.png \
    qml/emoji/D83CDF69.png \
    qml/emoji/D83CDF83.png \
    qml/emoji/D83CDFAA.png \
    qml/emoji/D83CDFB1.png \
    qml/emoji/D83CDFB2.png \
    qml/emoji/D83CDFB7.png \
    qml/emoji/D83CDFB8.png \
    qml/emoji/D83CDFBE.png \
    qml/emoji/D83CDFC0.png \
    qml/emoji/D83CDFE6.png \
    qml/emoji/26BD.png \
    qml/emoji/26C5.png \
    qml/emoji/23F3.png \
    qml/emoji/26BE.png \
    qml/emoji/26C4.png \
    qml/emoji/2600.png \
    qml/emoji/261D.png \
    qml/emoji/270C.png \
    qml/emoji/2764.png \
    qml/pages/TextEx.qml \
    qml/fonts/AppleColorEmoji.ttf \
    qml/fonts/OpenSansEmoji.ttf

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n
TRANSLATIONS += translations/harbour-vk-de.ts
CONFIG += precompile_header
PRECOMPILED_HEADER += src/debug.h

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
    src/vkcontainerlink.h \
    src/debuglogbuffer.h \
    src/vklpunreadcount.h \
    src/vknetworkmanager.h \
    src/vkhandlerlongpollserverkey.h \
    src/vkemojiparser.h \
    src/vkemojiparserdata.h \
    src/vktextwrap.h

RESOURCES +=

