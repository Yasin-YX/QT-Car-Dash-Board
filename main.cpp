#include "mainwindow.h"

#include "udpsend.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

   UdpSend & t =  UdpSend::getUdp();
   t.setServerInfo("127.0.0.1",12345);

    MainWindow w;
    w.show();
    return a.exec();
}
