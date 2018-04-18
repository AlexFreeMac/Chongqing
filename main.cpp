#include <QCoreApplication>
#include <QDebug>
#include "readconfigfile.h"
#include "mainworkflow.h"
quint16 g_TransportUdpPort;
QString g_strTransforIP;
quint16 g_LocalUdpPort;
QString g_strLocalIP;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<"Start";

    MainWorkFlow mainwork;

    return a.exec();
}
