#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    m_session = new QNetworkSession(QNetworkConfiguration(),this);
    m_server = new QTcpServer(this);
    m_clients = new QQmlObjectListModel<Client>();
    if(!m_server->listen(QHostAddress("192.168.1.110"),55443)) qFatal("Unable to start the server: %1.");
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    qDebug() <<
                "The server is running on\n\nIP:" <<
                ipAddress << "\nport: "<<
                m_server->serverPort() <<
                "\n\n" << "Run the Fortune Client example now.";
    connect(m_server,SIGNAL(newConnection()),
            this,SLOT(onNewConnection()));
}

void Server::onNewConnection()
{
    while(m_server->hasPendingConnections()) {
        QTcpSocket *socket = m_server->nextPendingConnection();
        qDebug() << "NEW CONNECTION ESTABLISHED!";
        Client *c = new Client(socket);
        connect(c,SIGNAL(disconnection()),
                this,SLOT(onDisconnection()));
        connect(c,SIGNAL(ready(QJsonObject)),
                this,SLOT(onReady(QJsonObject)));
        m_clients->append(c);
    }
}

void Server::onDisconnection()
{
    Client *c = static_cast<Client*>(sender());
    m_clients->remove(c);
    qDebug() << "DISCONNETING: " << c->get_name();
    notifyAllClients();
    c->deleteLater();
}

void Server::onReady(QJsonObject obj)
{
    QByteArray op = obj["op"].toString().toLatin1();
    if(op=="Register") {
        Client *c = static_cast<Client*>(sender());
        c->set_name(obj["name"].toString().toLatin1());
        c->set_id(obj["id"].toString().toLatin1());
        notifyAllClients();
    } else if(op=="Message") {

    }
}

QByteArray Server::clientsToJson()
{
    QJsonObject mainObj;
    mainObj.insert("op","friends");
    QJsonArray clients;
    for(int i=0;i<m_clients->size();i++) {
        QJsonObject client;
        client.insert("name",QString(m_clients->at(i)->get_name()));
        client.insert("id",QString(m_clients->at(i)->get_id()));
        clients.append(client);
    }
    mainObj.insert("clients",clients);
    QJsonDocument doc(mainObj);
    return doc.toJson();
}

void Server::notifyAllClients()
{
    for(int i=0;i<m_clients->size();i++) {
        Client *client = m_clients->at(i);
        client->get_socket()->write(clientsToJson());
    }
}
