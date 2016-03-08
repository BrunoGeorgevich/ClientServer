#include "client.h"

Client::Client(QTcpSocket *socket, QByteArray name, QByteArray id, QObject *parent)
    : QObject(parent)
{
    m_socket=socket;m_name=name; m_cid=id;
    connect(m_socket,SIGNAL(readyRead()),
            this,SLOT(onReadyRead()));
    connect(m_socket,SIGNAL(disconnected()),
            this,SLOT(onDisconnects()));
}

void Client::onReadyRead()
{
    QJsonDocument doc = QJsonDocument::fromJson(m_socket->readAll());
    emit ready(doc.object());
}

void Client::onDisconnects()
{
    emit disconnection();
}
