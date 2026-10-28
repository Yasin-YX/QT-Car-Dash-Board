#include "udpsend.h"
#include <QDebug>

UdpSend::UdpSend()
{
    socket = new QUdpSocket();
}

UdpSend::UdpSend(const UdpSend &other)
{

}

UdpSend &UdpSend::getUdp()
{
    static UdpSend temp;
    return temp;
}

void UdpSend::setServerInfo(QString ip, quint16 port)
{
    this->serverIP = ip;
    this->serverPort = port;
}

void UdpSend::sendUdpJsonData()
{
   QJsonObject obj = CarCongig::getCar().buildJsonObject();
   QJsonDocument doc(obj);
   QByteArray arr = doc.toJson(QJsonDocument::Compact);
   socket->writeDatagram(arr,QHostAddress(serverIP),serverPort );
}
