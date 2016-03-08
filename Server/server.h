#ifndef NETWORK_H
#define NETWORK_H

#include <QNetworkSession>
#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QDebug>
#include "../brunocppessencials/qqmlhelpers.h"
#include "../brunocppessencials/qqmlobjectlistmodel.h"
#include "client.h"

class Server : public QObject
{
    Q_OBJECT
    QML_OBJMODEL_PROPERTY(Client,clients)
public:
    explicit Server(QObject *parent = 0);
public slots:
    void onNewConnection();
    void onDisconnection();
    void onReady(QJsonObject obj);
private:
    QByteArray clientsToJson();
    void notifyAllClients();
    void newMessageSend(QJsonObject message);
    QNetworkSession *m_session;
    QTcpServer *m_server;
};

#endif // NETWORK_H
