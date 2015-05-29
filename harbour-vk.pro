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

CONFIG += sailfishapp c++11

SOURCES += src/harbour-vk.cpp \
    src/vk.cpp \
    src/cryptostorage.cpp \
    src/cachestorage.cpp \
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
    src/storageasynchronous.cpp \
    src/vklongpollserver.cpp \
    src/vkcontainerchaticon.cpp \
    src/vkqmlnetworkaccessmanagerfactor.cpp \
    src/vknetworkaccessmanager.cpp \
    src/vklongpollupdateparser.cpp \
    src/vklongpollcontainer.cpp \
    src/vkhandlerlongpollupdatedata.cpp \
    src/qmllist.cpp

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
    qml/pages/MessageComponent.qml \
    qml/pages/__MessageElement.qml \
    qml/pages/Friends.qml \
    qml/pages/DialogIconHolder.qml \
    qml/pages/FriendComponent.qml \
    qml/pages/MessageFwdElement.qml \
    qml/pages/MessageData.qml \
    qml/pages/MultiImage.qml \
    qml/handlers.js \
    qml/cache.js \
    qml/pages/ImageCached.qml

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n
TRANSLATIONS += translations/harbour-vk-de.ts

# DEFINES += "PREVIEW_LENGTH=16"

HEADERS += \
    src/vk.h \
    src/cryptostorage.h \
    src/cachestorage.h \
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
    src/storageasynchronous.h \
    src/vklongpollserver.h \
    src/vkcontainerchaticon.h \
    src/vkqmlnetworkaccessmanagerfactor.h \
    src/vknetworkaccessmanager.h \
    src/vklongpollupdateparser.h \
    src/vklongpollcontainer.h \
    src/vkhandlerlongpollupdatedata.h \
    src/qmllist.h

RESOURCES +=

