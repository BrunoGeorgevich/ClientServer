#include <QQmlContext>
#include <QApplication>
#include <QQmlApplicationEngine>
#include "client.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client *c = new Client("Bruno");
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("_client",c);
    engine.load(QUrl("qrc:/main.qml"));
    return a.exec();
}

