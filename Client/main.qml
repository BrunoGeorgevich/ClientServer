import QtQuick 2.5
import QtQuick.Controls 1.4

ApplicationWindow {
    id:root
    visible: true
    width: 800; height: 600
    ListView {
        anchors.fill: parent
        model:_client.friends
        spacing:50
        delegate: Rectangle {
            width: parent.width; height: 100
            color: "black"
        }
    }
}
