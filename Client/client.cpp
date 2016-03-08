#include "client.h"

Client::Client(QByteArray name, QObject *parent) : QObject(parent)
{
    qsrand(static_cast<uint>(QTime::currentTime().msec()));
    m_socket = new QTcpSocket(this);
    m_socket->connectToHost("192.168.1.103",55443);
    m_friends = new QQmlObjectListModel<Friend>();
    m_messages = new QQmlObjectListModel<Message>();
    m_name=name; m_fid = QByteArray::number((qrand()%89999999)+10000000);
    connect(m_socket,SIGNAL(connected()),
            this,SLOT(onConnected()));
    connect(m_socket,SIGNAL(readyRead()),
            this,SLOT(onReadyRead()));
}

void Client::onConnected()
{
    qDebug() << "HOST CONNECTED: " << m_socket->state();
    QJsonObject mainObj;
    mainObj.insert("op","register");
    mainObj.insert("name",QString(m_name));
    mainObj.insert("id",QString(m_fid));
    QJsonDocument doc(mainObj);
    m_socket->write(doc.toJson());
}

void Client::onReadyRead()
{
    QJsonDocument reply = QJsonDocument::fromJson(m_socket->readAll());
    QJsonObject mainObj = reply.object();
    if(mainObj["op"]=="friends") {
        m_friends->clear();
        QVariantList friends = mainObj["clients"].toArray().toVariantList();
        foreach (QVariant f, friends) {
            if(m_fid==f.toMap()["id"].toString().toLatin1()) continue;
            Friend *nFriend = new Friend(
                        f.toMap()["name"].toString().toLatin1(),
                    f.toMap()["id"].toString().toLatin1(),
                    this
                    );
            m_friends->append(nFriend);
        }
    } else if(mainObj["op"]=="message") {
        m_messages->append(
                    new Message(
                        mainObj["sender"].toString(),
                        mainObj["content"].toString(),
                        this
                    )
                );
    }
}

bool Client::sendMessage(QString message)
{
    QJsonObject mainObj;
    mainObj.insert("op","message");
    mainObj.insert("sender",QString(m_name));
    mainObj.insert("content",message);
    QJsonDocument doc(mainObj);
    qint64 size = m_socket->write(doc.toJson());
    if(size==0) return false;
    return true;
}

