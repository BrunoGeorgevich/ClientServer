#ifndef CLIENT_H
#define CLIENT_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QObject>
#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "../brunocppessencials/qqmlobjectlistmodel.h"
#include "../brunocppessencials/qqmlhelpers.h"
#include "friend.h"
#include "message.h"

class Client : public QObject
{
    Q_OBJECT
    QML_OBJMODEL_PROPERTY(Friend,friends)
    QML_OBJMODEL_PROPERTY(Message,messages)
    QML_READONLY_PROPERTY(QByteArray,name)
    QML_READONLY_PROPERTY(QByteArray,fid)
public:
    explicit Client(QByteArray name, QObject *parent = 0);
    Q_INVOKABLE bool sendMessage(QString message);
public slots:
    void onConnected();
    void onReadyRead();
private:
    QTcpSocket *m_socket;
};

#endif // CLIENT_H
