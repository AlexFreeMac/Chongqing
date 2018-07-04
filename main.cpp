#include <QCoreApplication>
#include <QDebug>
#include "readconfigfile.h"
#include "mainworkflow.h"
#include <QThread>
#include <QTextCodec>
#include <shiftantenna.h>
#include <QSemaphore>
quint16 g_TransportUdpPort;
QString g_strTransforIP;
quint16 g_LocalUdpPort;
QString g_strLocalIP;
quint16 g_RadioStationUdpPort;
QString g_strRadioStationIP;
QString g_strGetFreqUdpIP;
quint16 g_GetFreqUdpPort;
bool g_isUseSerial;
char g_BUFF[1024];
int g_WriteIndex = 0;
int g_ReadIndex = 0;
QSemaphore g_freeBytes(1024);
QSemaphore g_usedBytes(0);
QThread g_Thread;
QThread g_ShiftAntennaThread;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<"Start";
    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(utf8);
    qDebug()<<__FUNCTION__<<"CurrentThread"<<QThread::currentThread();
    MainWorkFlow mainwork;
//    mainwork.moveToThread(&g_Thread);
//    g_Thread.start();
    return a.exec();
}
