#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "server.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server *server = new Server();
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("_server",server);
    engine.load(QUrl("qrc:/main.qml"));
    return a.exec();
}

