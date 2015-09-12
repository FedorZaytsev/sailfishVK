import QtQuick 2.0
import Sailfish.Silica 1.0
import QtWebKit 3.0
//todo HTTPS pass

Page {
    id: authPage

    WebView {
        id: authWebView
        visible: !vk.isOurUserAuthorized()

        anchors.fill: parent

        url: vk.getAuthPageUrl()
        onLoadingChanged: {
            function openMessanges() {
                vk.startLongPollServer(true)
                pageStack.replace(Qt.resolvedUrl("Dialogs.qml"),{})
            }

            console.log("On loading changed",loadRequest.url)
            if (vk.isOurUserAuthorized()) {
                openMessanges()
                return
            }

            switch (loadRequest.status) {
            case WebView.LoadSucceededStatus:
                if (vk.updateAccessToken(loadRequest.url)) {
                    openMessanges()
                }

                break
            case WebView.LoadFailedStatus:
                console.log("Some error while loading page, reloading")
                authWebView.url = vk.getAuthPageUrl()            //Reload
                break
            }
        }
    }
}
