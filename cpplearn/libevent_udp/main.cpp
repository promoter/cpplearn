#include <QApplication>
#include <QTextCodec>
#include <QDebug>

#include <QtSql/QSqlDatabase>
#include <QStringList>

#include "udp_multicast.h"

int main(int argc, char *argv[]) 
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));

    QStringList drivers = QSqlDatabase::drivers();
    qDebug() << drivers;

    UdpMulticast udpTest;
    udpTest.Start();

    UdpMulticast::StartEventThread(&udpTest);

    return a.exec();
}
