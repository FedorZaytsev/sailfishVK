import QtQuick 2.0

Item {
    width: 100
    height: 100

    Loader {
        sourceComponent: {
            function check(el) {
                return el && el !== ""
            }
            if (check(icon1) && check(icon2) && check(icon3) && check(icon4)) {
                return fourIconsView
            } else if (check(icon1) && check(icon2)) {
                return twoIconsView
            } else {
                if (!icon1) {
                    icon1 = "http:\/\/vk.com\/images\/camera_100.gif"
                }
                return singleIconView
            }
        }
    }

    Component {
        id: singleIconView
        Image {
            width: 100
            height: 100
            source: icon1

        }
    }
    Component {
        id: fourIconsView
        Grid {
            columns: 2
            Image {width:50;height:50;source:icon1;}
            Image {width:50;height:50;source:icon2;}
            Image {width:50;height:50;source:icon3;}
            Image {width:50;height:50;source:icon4;}
        }
    }
    Component {
        id: twoIconsView
        Row {
            Image {width:50;height:100;source:icon1;fillMode: Image.PreserveAspectCrop;}
            Image {width:50;height:100;source:icon2;fillMode: Image.PreserveAspectCrop;}
        }
    }

}
