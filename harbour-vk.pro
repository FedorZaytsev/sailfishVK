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
QMAKE_CXXFLAGS += -Werror -std=c++0x -g -rdynamic
LIBS += -ldl

CONFIG += sailfishapp c++11

#CONFIG(ARMV7,ARMV7|I486):LIBS += ""
#CONFIG(I486,ARMV7|I486):LIBS += ""

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
    src/vkemojiparser.cpp \
    src/vktextwrap.cpp \
    src/vkfilestorage.cpp \
    src/vkvisualdialogmodel.cpp \
    src/vkstoragecomparator.cpp \
    src/vkvisualmessagemodel.cpp \
    src/vkvisibleparseattachments.cpp \
    src/vkadditionaldatapair.cpp \
    src/ivkcompletable.cpp \
    src/vkadditionalhelper.cpp \
    src/vkhandlerfirstmessage.cpp \
    src/vkhandlermessagebyid.cpp \
    src/vkhandlerdialogbyid.cpp \
    src/vkusertyping.cpp

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
    qml/emoji/D83DDE04.png \
    qml/emoji/D83DDE07.png \
    qml/emoji/D83DDE30.png \
    qml/emoji/D83DDE32.png \
    qml/emoji/D83DDE33.png \
    qml/emoji/D83DDE37.png \
    qml/emoji/D83DDE02.png \
    qml/emoji/2764.png \
    qml/emoji/D83DDE1A.png \
    qml/emoji/D83DDE15.png \
    qml/emoji/D83DDE2F.png \
    qml/emoji/D83DDE26.png \
    qml/emoji/D83DDE35.png \
    qml/emoji/D83DDE20.png \
    qml/emoji/D83DDE21.png \
    qml/emoji/D83DDE1D.png \
    qml/emoji/D83DDE34.png \
    qml/emoji/D83DDE18.png \
    qml/emoji/D83DDE1F.png \
    qml/emoji/D83DDE2C.png \
    qml/emoji/D83DDE36.png \
    qml/emoji/D83DDE2A.png \
    qml/emoji/D83DDE2B.png \
    qml/emoji/263A.png \
    qml/emoji/D83DDE00.png \
    qml/emoji/D83DDE25.png \
    qml/emoji/D83DDE1B.png \
    qml/emoji/D83DDE16.png \
    qml/emoji/D83DDE24.png \
    qml/emoji/D83DDE23.png \
    qml/emoji/D83DDE27.png \
    qml/emoji/D83DDE11.png \
    qml/emoji/D83DDE05.png \
    qml/emoji/D83DDE2E.png \
    qml/emoji/D83DDE1E.png \
    qml/emoji/D83DDE19.png \
    qml/emoji/D83DDE13.png \
    qml/emoji/D83DDE01.png \
    qml/emoji/D83DDE31.png \
    qml/emoji/D83DDE08.png \
    qml/emoji/D83DDC7F.png \
    qml/emoji/D83DDC7D.png \
    qml/emoji/D83DDC4D.png \
    qml/emoji/D83DDC4E.png \
    qml/emoji/261D.png \
    qml/emoji/270C.png \
    qml/emoji/D83DDC4C.png \
    qml/emoji/D83DDC4F.png \
    qml/emoji/D83DDC4A.png \
    qml/emoji/270B.png \
    qml/emoji/D83DDE4F.png \
    qml/emoji/D83DDC43.png \
    qml/emoji/D83DDC46.png \
    qml/emoji/D83DDC47.png \
    qml/emoji/D83DDC48.png \
    qml/emoji/D83DDCAA.png \
    qml/emoji/D83DDC42.png \
    qml/emoji/D83DDC8B.png \
    qml/emoji/D83DDCA9.png \
    qml/emoji/2744.png \
    qml/emoji/D83CDF4A.png \
    qml/emoji/D83CDF77.png \
    qml/emoji/D83CDF78.png \
    qml/emoji/D83CDF85.png \
    qml/emoji/D83DDCA6.png \
    qml/emoji/D83DDC7A.png \
    qml/emoji/D83DDC28.png \
    qml/emoji/D83DDD1E.png \
    qml/emoji/D83DDC79.png \
    qml/emoji/26BD.png \
    qml/emoji/26C5.png \
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
    qml/emoji/23F3.png \
    qml/emoji/26BE.png \
    qml/emoji/26C4.png \
    qml/emoji/2600.png \
    qml/emoji/D83CDF3A.png \
    qml/emoji/D83CDF3B.png \
    qml/emoji/D83CDF3C.png \
    qml/emoji/D83CDF3D.png \
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
    qml/emoji/D83DDE38.png \
    qml/emoji/D83DDE39.png \
    qml/emoji/D83DDE3C.png \
    qml/emoji/D83DDE3D.png \
    qml/emoji/D83DDE3E.png \
    qml/emoji/D83DDE3F.png \
    qml/emoji/D83DDE3B.png \
    qml/emoji/D83DDE40.png \
    qml/emoji/D83DDE3A.png \
    qml/emoji/23F0.png \
    qml/emoji/2601.png \
    qml/emoji/260E.png \
    qml/emoji/2615.png \
    qml/emoji/267B.png \
    qml/emoji/26A0.png \
    qml/emoji/26A1.png \
    qml/emoji/26D4.png \
    qml/emoji/26EA.png \
    qml/emoji/26F3.png \
    qml/emoji/26F5.png \
    qml/emoji/26FD.png \
    qml/emoji/2702.png \
    qml/emoji/2708.png \
    qml/emoji/2709.png \
    qml/emoji/270A.png \
    qml/emoji/270F.png \
    qml/emoji/2712.png \
    qml/emoji/2728.png \
    qml/emoji/D83CDC04.png \
    qml/emoji/D83CDCCF.png \
    qml/emoji/D83CDD98.png \
    qml/emoji/D83CDF02.png \
    qml/emoji/D83CDF0D.png \
    qml/emoji/D83CDF1B.png \
    qml/emoji/D83CDF1D.png \
    qml/emoji/D83CDF1E.png \
    qml/emoji/D83CDF30.png \
    qml/emoji/D83CDF31.png \
    qml/emoji/D83CDF32.png \
    qml/emoji/D83CDF33.png \
    qml/emoji/D83CDF34.png \
    qml/emoji/D83CDF35.png \
    qml/emoji/D83CDF3E.png \
    qml/emoji/D83CDF3F.png \
    qml/emoji/D83CDF40.png \
    qml/emoji/D83CDF41.png \
    qml/emoji/D83CDF42.png \
    qml/emoji/D83CDF43.png \
    qml/emoji/D83CDF44.png \
    qml/emoji/D83CDF47.png \
    qml/emoji/D83CDF48.png \
    qml/emoji/D83CDF5A.png \
    qml/emoji/D83CDF5B.png \
    qml/emoji/D83CDF5C.png \
    qml/emoji/D83CDF5D.png \
    qml/emoji/D83CDF5E.png \
    qml/emoji/D83CDF5F.png \
    qml/emoji/D83CDF60.png \
    qml/emoji/D83CDF61.png \
    qml/emoji/D83CDF62.png \
    qml/emoji/D83CDF63.png \
    qml/emoji/D83CDF64.png \
    qml/emoji/D83CDF65.png \
    qml/emoji/D83CDF66.png \
    qml/emoji/D83CDF67.png \
    qml/emoji/D83CDF68.png \
    qml/emoji/D83CDF6A.png \
    qml/emoji/D83CDF6B.png \
    qml/emoji/D83CDF6C.png \
    qml/emoji/D83CDF6E.png \
    qml/emoji/D83CDF6F.png \
    qml/emoji/D83CDF70.png \
    qml/emoji/D83CDF71.png \
    qml/emoji/D83CDF72.png \
    qml/emoji/D83CDF73.png \
    qml/emoji/D83CDF74.png \
    qml/emoji/D83CDF75.png \
    qml/emoji/D83CDF76.png \
    qml/emoji/D83CDF79.png \
    qml/emoji/D83CDF7C.png \
    qml/emoji/D83CDF80.png \
    qml/emoji/D83CDF88.png \
    qml/emoji/D83CDF89.png \
    qml/emoji/D83CDF8A.png \
    qml/emoji/D83CDF8B.png \
    qml/emoji/D83CDF8C.png \
    qml/emoji/D83CDF8D.png \
    qml/emoji/D83CDF8E.png \
    qml/emoji/D83CDF8F.png \
    qml/emoji/D83CDF90.png \
    qml/emoji/D83CDF92.png \
    qml/emoji/D83CDF93.png \
    qml/emoji/D83CDFA3.png \
    qml/emoji/D83CDFA4.png \
    qml/emoji/D83CDFA7.png \
    qml/emoji/D83CDFA8.png \
    qml/emoji/D83CDFA9.png \
    qml/emoji/D83CDFAB.png \
    qml/emoji/D83CDFAC.png \
    qml/emoji/D83CDFAD.png \
    qml/emoji/D83CDFAF.png \
    qml/emoji/D83CDFB0.png \
    qml/emoji/D83CDFB3.png \
    qml/emoji/D83CDFB4.png \
    qml/emoji/D83CDFB9.png \
    qml/emoji/D83CDFBA.png \
    qml/emoji/D83CDFBB.png \
    qml/emoji/D83CDFBD.png \
    qml/emoji/D83CDFBF.png \
    qml/emoji/D83CDFC2.png \
    qml/emoji/D83CDFC3.png \
    qml/emoji/D83CDFC4.png \
    qml/emoji/D83CDFC7.png \
    qml/emoji/D83CDFC8.png \
    qml/emoji/D83CDFC9.png \
    qml/emoji/D83CDFCA.png \
    qml/emoji/D83DDC00.png \
    qml/emoji/D83DDC01.png \
    qml/emoji/D83DDC02.png \
    qml/emoji/D83DDC04.png \
    qml/emoji/D83DDC06.png \
    qml/emoji/D83DDC07.png \
    qml/emoji/D83DDC08.png \
    qml/emoji/D83DDC09.png \
    qml/emoji/D83DDC0A.png \
    qml/emoji/D83DDC0B.png \
    qml/emoji/D83DDC0C.png \
    qml/emoji/D83DDC0D.png \
    qml/emoji/D83DDC10.png \
    qml/emoji/D83DDC12.png \
    qml/emoji/D83DDC14.png \
    qml/emoji/D83DDC15.png \
    qml/emoji/D83DDC16.png \
    qml/emoji/D83DDC17.png \
    qml/emoji/D83DDC19.png \
    qml/emoji/D83DDC1A.png \
    qml/emoji/D83DDC1B.png \
    qml/emoji/D83DDC1D.png \
    qml/emoji/D83DDC1E.png \
    qml/emoji/D83DDC1F.png \
    qml/emoji/D83DDC20.png \
    qml/emoji/D83DDC21.png \
    qml/emoji/D83DDC22.png \
    qml/emoji/D83DDC23.png \
    qml/emoji/D83DDC24.png \
    qml/emoji/D83DDC25.png \
    qml/emoji/D83DDC26.png \
    qml/emoji/D83DDC27.png \
    qml/emoji/D83DDC29.png \
    qml/emoji/D83DDC2A.png \
    qml/emoji/D83DDC2C.png \
    qml/emoji/D83DDC2D.png \
    qml/emoji/D83DDC2F.png \
    qml/emoji/D83DDC30.png \
    qml/emoji/D83DDC32.png \
    qml/emoji/D83DDC33.png \
    qml/emoji/D83DDC34.png \
    qml/emoji/D83DDC35.png \
    qml/emoji/D83DDC38.png \
    qml/emoji/D83DDC39.png \
    qml/emoji/D83DDC3A.png \
    qml/emoji/D83DDC3D.png \
    qml/emoji/D83DDC3E.png \
    qml/emoji/D83DDC40.png \
    qml/emoji/D83DDC44.png \
    qml/emoji/D83DDC45.png \
    qml/emoji/D83DDC4B.png \
    qml/emoji/D83DDC50.png \
    qml/emoji/D83DDC51.png \
    qml/emoji/D83DDC52.png \
    qml/emoji/D83DDC53.png \
    qml/emoji/D83DDC54.png \
    qml/emoji/D83DDC55.png \
    qml/emoji/D83DDC56.png \
    qml/emoji/D83DDC57.png \
    qml/emoji/D83DDC58.png \
    qml/emoji/D83DDC59.png \
    qml/emoji/D83DDC5A.png \
    qml/emoji/D83DDC5B.png \
    qml/emoji/D83DDC5C.png \
    qml/emoji/D83DDC5D.png \
    qml/emoji/D83DDC5E.png \
    qml/emoji/D83DDC5F.png \
    qml/emoji/D83DDC60.png \
    qml/emoji/D83DDC61.png \
    qml/emoji/D83DDC62.png \
    qml/emoji/D83DDC63.png \
    qml/emoji/D83DDC66.png \
    qml/emoji/D83DDC67.png \
    qml/emoji/D83DDC68.png \
    qml/emoji/D83DDC69.png \
    qml/emoji/D83DDC6A.png \
    qml/emoji/D83DDC6B.png \
    qml/emoji/D83DDC6C.png \
    qml/emoji/D83DDC6D.png \
    qml/emoji/D83DDC6E.png \
    qml/emoji/D83DDC6F.png \
    qml/emoji/D83DDC70.png \
    qml/emoji/D83DDC71.png \
    qml/emoji/D83DDC72.png \
    qml/emoji/D83DDC73.png \
    qml/emoji/D83DDC74.png \
    qml/emoji/D83DDC75.png \
    qml/emoji/D83DDC76.png \
    qml/emoji/D83DDC77.png \
    qml/emoji/D83DDC78.png \
    qml/emoji/D83DDC7B.png \
    qml/emoji/D83DDC7C.png \
    qml/emoji/D83DDC7E.png \
    qml/emoji/D83DDC80.png \
    qml/emoji/D83DDC81.png \
    qml/emoji/D83DDC82.png \
    qml/emoji/D83DDC83.png \
    qml/emoji/D83DDC84.png \
    qml/emoji/D83DDC85.png \
    qml/emoji/D83DDC86.png \
    qml/emoji/D83DDC87.png \
    qml/emoji/D83DDC88.png \
    qml/emoji/D83DDC89.png \
    qml/emoji/D83DDC8A.png \
    qml/emoji/D83DDC8C.png \
    qml/emoji/D83DDC8D.png \
    qml/emoji/D83DDC8E.png \
    qml/emoji/D83DDC8F.png \
    qml/emoji/D83DDC90.png \
    qml/emoji/D83DDC91.png \
    qml/emoji/D83DDC92.png \
    qml/emoji/D83DDC93.png \
    qml/emoji/D83DDC95.png \
    qml/emoji/D83DDC96.png \
    qml/emoji/D83DDC97.png \
    qml/emoji/D83DDC98.png \
    qml/emoji/D83DDC99.png \
    qml/emoji/D83DDC9A.png \
    qml/emoji/D83DDC9B.png \
    qml/emoji/D83DDC9C.png \
    qml/emoji/D83DDC9D.png \
    qml/emoji/D83DDC9E.png \
    qml/emoji/D83DDC9F.png \
    qml/emoji/D83DDCA1.png \
    qml/emoji/D83DDCA3.png \
    qml/emoji/D83DDCA5.png \
    qml/emoji/D83DDCA7.png \
    qml/emoji/D83DDCA8.png \
    qml/emoji/D83DDCAC.png \
    qml/emoji/D83DDCB0.png \
    qml/emoji/D83DDCB3.png \
    qml/emoji/D83DDCB4.png \
    qml/emoji/D83DDCB5.png \
    qml/emoji/D83DDCB6.png \
    qml/emoji/D83DDCB7.png \
    qml/emoji/D83DDCB8.png \
    qml/emoji/D83DDCBA.png \
    qml/emoji/D83DDCBB.png \
    qml/emoji/D83DDCBC.png \
    qml/emoji/D83DDCBD.png \
    qml/emoji/D83DDCBE.png \
    qml/emoji/D83DDCBF.png \
    qml/emoji/D83DDCC4.png \
    qml/emoji/D83DDCC5.png \
    qml/emoji/D83DDCC7.png \
    qml/emoji/D83DDCC8.png \
    qml/emoji/D83DDCC9.png \
    qml/emoji/D83DDCCA.png \
    qml/emoji/D83DDCCB.png \
    qml/emoji/D83DDCCC.png \
    qml/emoji/D83DDCCD.png \
    qml/emoji/D83DDCCE.png \
    qml/emoji/D83DDCD0.png \
    qml/emoji/D83DDCD1.png \
    qml/emoji/D83DDCD2.png \
    qml/emoji/D83DDCD3.png \
    qml/emoji/D83DDCD4.png \
    qml/emoji/D83DDCD5.png \
    qml/emoji/D83DDCD6.png \
    qml/emoji/D83DDCD7.png \
    qml/emoji/D83DDCD8.png \
    qml/emoji/D83DDCD9.png \
    qml/emoji/D83DDCDA.png \
    qml/emoji/D83DDCDC.png \
    qml/emoji/D83DDCDD.png \
    qml/emoji/D83DDCDF.png \
    qml/emoji/D83DDCE0.png \
    qml/emoji/D83DDCE1.png \
    qml/emoji/D83DDCE2.png \
    qml/emoji/D83DDCE6.png \
    qml/emoji/D83DDCED.png \
    qml/emoji/D83DDCEE.png \
    qml/emoji/D83DDCEF.png \
    qml/emoji/D83DDCF0.png \
    qml/emoji/D83DDCF1.png \
    qml/emoji/D83DDCF7.png \
    qml/emoji/D83DDCF9.png \
    qml/emoji/D83DDCFA.png \
    qml/emoji/D83DDCFB.png \
    qml/emoji/D83DDCFC.png \
    qml/emoji/D83DDD06.png \
    qml/emoji/D83DDD0E.png \
    qml/emoji/D83DDD11.png \
    qml/emoji/D83DDD14.png \
    qml/emoji/D83DDD16.png \
    qml/emoji/D83DDD25.png \
    qml/emoji/D83DDD26.png \
    qml/emoji/D83DDD27.png \
    qml/emoji/D83DDD28.png \
    qml/emoji/D83DDD29.png \
    qml/emoji/D83DDD2A.png \
    qml/emoji/D83DDD2B.png \
    qml/emoji/D83DDD2C.png \
    qml/emoji/D83DDD2D.png \
    qml/emoji/D83DDD2E.png \
    qml/emoji/D83DDD31.png \
    qml/emoji/D83DDDFF.png \
    qml/emoji/D83DDE45.png \
    qml/emoji/D83DDE46.png \
    qml/emoji/D83DDE47.png \
    qml/emoji/D83DDE48.png \
    qml/emoji/D83DDE49.png \
    qml/emoji/D83DDE4A.png \
    qml/emoji/D83DDE4B.png \
    qml/emoji/D83DDE4C.png \
    qml/emoji/D83DDE4E.png \
    qml/emoji/D83DDE80.png \
    qml/emoji/D83DDE81.png \
    qml/emoji/D83DDE82.png \
    qml/emoji/D83DDE83.png \
    qml/emoji/D83DDE84.png \
    qml/emoji/D83DDE85.png \
    qml/emoji/D83DDE86.png \
    qml/emoji/D83DDE87.png \
    qml/emoji/D83DDE88.png \
    qml/emoji/D83DDE8A.png \
    qml/emoji/D83DDE8C.png \
    qml/emoji/D83DDE8D.png \
    qml/emoji/D83DDE8E.png \
    qml/emoji/D83DDE8F.png \
    qml/emoji/D83DDE90.png \
    qml/emoji/D83DDE91.png \
    qml/emoji/D83DDE92.png \
    qml/emoji/D83DDE93.png \
    qml/emoji/D83DDE94.png \
    qml/emoji/D83DDE95.png \
    qml/emoji/D83DDE96.png \
    qml/emoji/D83DDE97.png \
    qml/emoji/D83DDE98.png \
    qml/emoji/D83DDE99.png \
    qml/emoji/D83DDE9A.png \
    qml/emoji/D83DDE9B.png \
    qml/emoji/D83DDE9C.png \
    qml/emoji/D83DDE9D.png \
    qml/emoji/D83DDE9E.png \
    qml/emoji/D83DDE9F.png \
    qml/emoji/D83DDEA0.png \
    qml/emoji/D83DDEA1.png \
    qml/emoji/D83DDEA3.png \
    qml/emoji/D83DDEA4.png \
    qml/emoji/D83DDEA7.png \
    qml/emoji/D83DDEA8.png \
    qml/emoji/D83DDEAA.png \
    qml/emoji/D83DDEAC.png \
    qml/emoji/D83DDEB4.png \
    qml/emoji/D83DDEB5.png \
    qml/emoji/D83DDEB6.png \
    qml/emoji/D83DDEBD.png \
    qml/emoji/D83DDEBF.png \
    qml/emoji/D83DDEC0.png \
    qml/emoji/D83CDDE8D83CDDF3.png \
    qml/emoji/D83CDDE9D83CDDEA.png \
    qml/emoji/D83CDDEAD83CDDF8.png \
    qml/emoji/D83CDDEBD83CDDF7.png \
    qml/emoji/D83CDDECD83CDDE7.png \
    qml/emoji/D83CDDEED83CDDF9.png \
    qml/emoji/D83CDDEFD83CDDF5.png \
    qml/emoji/D83CDDF0D83CDDF7.png \
    qml/emoji/D83CDDF7D83CDDFA.png \
    qml/emoji/D83CDDFAD83CDDF8.png \
    qml/emoji/D83DDD30.png \
    qml/emoji/D83CDDF0D83CDDFF.png \
    qml/emoji/D83CDDE7D83CDDFE.png \
    qml/pages/TextEx.qml \
    qml/fonts/OpenSansEmoji.ttf \
    qml/cover/ConversationComponent.qml \
    qml/main.js

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
    src/vktextwrap.h \
    src/vkfilestorage.h \
    src/vkstoragecomparator.h \
    src/vkvisualdialogmodel.h \
    src/vkvisualmessagemodel.h \
    src/vkvisibleparseattachments.h \
    src/vkadditionaldatapair.h \
    src/ivkcompletable.h \
    src/vkadditionalhelper.h \
    src/vkhandlerfirstmessage.h \
    src/vkhandlermessagebyid.h \
    src/vkhandlerdialogbyid.h \
    src/vkusertyping.h

RESOURCES +=

