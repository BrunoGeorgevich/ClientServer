#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include "../brunocppessencials/qqmlhelpers.h"

class Message : public QObject
{
    Q_OBJECT
    QML_READONLY_PROPERTY(QString,uSender)
    QML_READONLY_PROPERTY(QString,content)
public:
    explicit Message(QString uSender = "Nobody", QString content = "Empty", QObject *parent = 0);
};

#endif // MESSAGE_H
