QT += core network qml quick widgets

TARGET = Client
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    client.cpp \
    friend.cpp

HEADERS += \
    client.h \
    ../brunocppessencials/qqmlobjectlistmodel.h \
    friend.h

RESOURCES += \
    qml.qrc

