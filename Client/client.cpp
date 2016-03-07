#include "client.h"

Client::Client(QByteArray name, QObject *parent) : QObject(parent)
{
    qsrand(static_cast<uint>(QTime::currentTime().msec()));
    m_socket = new QTcpSocket(this);
    m_socket->connectToHost("192.168.1.110",55443);
    m_name=name; m_id = QByteArray::number((qrand()%89999999)+10000000);
    connect(m_socket,SIGNAL(connected()),
            this,SLOT(onConnected()));
    connect(m_socket,SIGNAL(readyRead()),
            this,SLOT(onReadyRead()));
}

void Client::onConnected()
{
    qDebug() << "HOST CONNECTED: " << m_socket->state();
    QJsonObject mainObj;
    mainObj.insert("op","Register");
    mainObj.insert("name",QString(m_name));
    mainObj.insert("id",QString(m_id));
    QJsonDocument doc(mainObj);
    m_socket->write(doc.toJson());
}

void Client::onReadyRead()
{
    QJsonDocument reply = QJsonDocument::fromJson(m_socket->readAll());
    QJsonObject mainObj = reply.object();
    if(mainObj["op"]=="friends") {
        QVariantList friends = mainObj["clients"].toArray().toVariantList();
        foreach (QVariant f, friends) {
            if(m_id==f.toMap()["id"].toString().toLatin1()) continue;
            Friend *nFriend = new Friend(
                        f.toMap()["name"].toString().toLatin1(),
                        f.toMap()["id"].toString().toLatin1(),
                        this
                    );
            m_friends->append(nFriend);
        }
    } else {

    }
}
