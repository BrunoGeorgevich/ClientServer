#ifndef FRIEND_H
#define FRIEND_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>

#include "../brunocppessencials/qqmlhelpers.h"

class Friend : public QObject
{
    Q_OBJECT
    QML_WRITABLE_PROPERTY(QByteArray,name)
    QML_WRITABLE_PROPERTY(QByteArray,id)
public:
    explicit Friend(QByteArray n="Default", QByteArray id="-1", QObject *parent = 0);
};

#endif // FRIEND_H
