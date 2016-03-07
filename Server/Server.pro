QT += qml quick widgets network

TARGET = Server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    client.cpp \
    server.cpp

HEADERS += \
    ../brunocppessencials/qqmlobjectlistmodel.h \
    client.h \
    server.h

OTHER_FILES += main.qml

RESOURCES += \
    ../brunocomponents/components.qrc \
    qml.qrc

DISTFILES +=

