#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QObject>
#include "../brunocppessencials/qqmlhelpers.h"

class Client : public QObject
{
    Q_OBJECT
    QML_WRITABLE_PROPERTY(QTcpSocket*,socket)
    QML_WRITABLE_PROPERTY(QByteArray,name)
    QML_WRITABLE_PROPERTY(QByteArray,id)
public:
    explicit Client(
            QTcpSocket *socket=Q_NULLPTR,
            QByteArray name="default",
            QByteArray id="-1",
            QObject *parent = 0);
private slots:
    void onReadyRead();
    void onDisconnects();
signals:
    void ready(QJsonObject obj);
    void disconnection();
};

#endif // CLIENT_H
