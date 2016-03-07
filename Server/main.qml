import QtQuick 2.5
import QtQuick.Controls 1.4

import "qrc:/components" as C
import "qrc:/components/functions.js" as JS

ApplicationWindow {
    id:root
    visible:true
    width:800; height: 600

    ListView {
        anchors { fill: parent; margins: JS.hpercent(10,parent) }
        model:_server.clients
        delegate: C.Card {
            height: JS.hpercent(20,root); width: JS.wpercent(100,parent)
            Column {
                anchors { fill:parent; margins: JS.hpercent(20,parent) }
                spacing: JS.hpercent(10,parent)
                C.TextLine {
                    id:dataTextLine
                    placeholder: name
                    height:JS.hpercent(30,parent); width: JS.wpercent(80,parent)
                }
                C.Button {
                    height:JS.hpercent(50,parent); width: JS.wpercent(30,parent)
                    anchors.horizontalCenter: parent.horizontalCenter
                    text:"Send"
                    color: "#299"; textColor: "#DEDEDE"; pixelSize: JS.hpercent(50,this)
                    action.onClicked: {
                    }
                }
            }
        }
    }
}

