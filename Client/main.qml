import QtQuick 2.5
import QtQuick.Controls 1.4

import "qrc:/components" as C
import "qrc:/components/functions.js" as JS

ApplicationWindow {
    id:root
    visible: true
    title: _client.name
    width: 400; height: 400
    Rectangle {
        id:baseRect
        anchors.fill: parent
        color: "#8BC34A"
        C.Frame {
            anchors.fill: parent
            topBarHeightPercent: 8
            topBarColor: "#795548"
            bottomBarHeightPercent:0
            topBarContent : Item {
                anchors.fill: parent
                Row {
                    anchors { fill: parent; margins:JS.hpercent(10,parent) }
                    C.ImageButton {
                        height: JS.hpercent(100,parent); width: height
                        elevation:0; color: "transparent"
                        source: "qrc:/return.png"; zoom:1.2
                    }
                }
            }
            content: Column {
                anchors{ fill: parent; margins: JS.hpercent(5,parent) }
                spacing: JS.hpercent(5,parent)
                Item {
                    width: JS.wpercent(100,parent); height: JS.hpercent(70,parent)
                    Row {
                        anchors.fill: parent
                        spacing: JS.wpercent(2,parent)
                        Rectangle {
                            id:chatRect
                            width: JS.wpercent(78,parent); height: JS.hpercent(100,parent)
                            color:"#DCEDC8"
                            border.color: Qt.darker(baseRect.color,1.1)
                            ListView {
                                anchors { fill: parent; margins:JS.wpercent(5,parent) }
                                model: _client.messages
                                delegate: Item {
                                    width: JS.wpercent(90,chatRect); height: JS.hpercent(10,chatRect)
                                    Text {
                                        anchors.fill: parent
                                        horizontalAlignment: Text.AlignLeft
                                        verticalAlignment: Text.AlignVCenter
                                        text: uSender + " : " + content
                                    }
                                }
                            }
                        }
                        Rectangle {
                            id:friendsRect
                            width: JS.wpercent(20,parent); height: JS.hpercent(100,parent)
                            color:"#DCEDC8"
                            border.color: Qt.darker(baseRect.color,1.1)
                            ListView {
                                anchors { fill: parent; margins:JS.wpercent(5,parent) }
                                model:_client.friends
                                spacing:JS.hpercent(5,this)
                                delegate: Item {
                                    width: JS.wpercent(90,friendsRect); height: JS.hpercent(10,friendsRect)
                                    Text {
                                        anchors.centerIn: parent
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                        text:name; color:"#212121"
                                        font { family: "Helvetica"; pixelSize: JS.hpercent(80,this); weight: Font.ExtraLight }
                                    }
                                }
                            }
                        }
                    }
                }

                Rectangle {
                    width: JS.wpercent(100,parent); height: JS.hpercent(20,parent)
                    color:"#DCEDC8"; radius: height/20
                    border.color: Qt.darker(baseRect.color,1.1)
                    Row {
                        anchors { fill: parent; margins: JS.hpercent(10,parent) }
                        spacing: JS.wpercent(5,parent)
                        C.TextLine {
                            id:messageTextLine
                            height: JS.hpercent(40,parent); width: JS.wpercent(80,parent)
                            anchors.verticalCenter: parent.verticalCenter
                            placeholder: "Mensagem"
                        }
                        C.ImageButton {
                            height: JS.hpercent(80,parent); width: height
                            radius: width/2; color: "#795548"
                            source: "qrc:/send.png"; zoom: 1.2
                            anchors.verticalCenter: parent.verticalCenter
                            action.onClicked: {
                                if(!_client.sendMessage(messageTextLine.text)) {
                                    notificationSystem.coloredNotify("ERROR TO SEND THE MESSAGE","red");
                                } else {
                                    messageTextLine.text = "";
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    C.NotificationSystem {
        id:notificationSystem
        isOnTheTop: true
        centralized: true
    }
}
