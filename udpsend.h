#ifndef UDPSEND_H
#define UDPSEND_H

#include <QUdpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include "carcongig.h"

class UdpSend
{
    UdpSend();
    UdpSend(const UdpSend & other);

    QUdpSocket* socket;
    QString serverIP;
    quint16 serverPort;
public:
    static UdpSend& getUdp();
    void setServerInfo(QString ip,quint16 port);
    void sendUdpJsonData();
};

#endif // UDPSEND_H
