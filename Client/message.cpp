#include "message.h"

Message::Message(QString uSender, QString content, QObject *parent) : QObject(parent)
{
    m_uSender=uSender;m_content=content;
}

