#include <QCoreApplication>
#include <QDebug>
#include "readconfigfile.h"
#include "mainworkflow.h"
#include <QThread>
#include <QTextCodec>
#include <shiftantenna.h>
#include <QSemaphore>
#include <QMutex>
#include <QDateTime>
#include <QTextStream>
#include <iostream>
using namespace std;
quint16 g_TransportUdpPort;
QString g_strTransforIP;
quint16 g_LocalUdpPort;
QString g_strLocalIP;
quint16 g_RadioStationUdpPort;
QString g_strRadioStationIP;
QString g_strGetFreqUdpIP;
quint16 g_GetFreqUdpPort;
bool g_isUseSerial;
bool g_isSendFinished = true;
char g_BUFF[1024];
int g_WriteIndex = 0;
int g_ReadIndex = 0;
QSemaphore g_freeBytes(1024);
QSemaphore g_usedBytes(0);
QThread g_Thread;
QThread g_ShiftAntennaThread;
void logOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();
    QString text;

    switch(type)
    {
        case QtDebugMsg:
        text = "Debug:";
        break;
        case QtWarningMsg:
        text = "Waring";
        break;
        case QtCriticalMsg:
        text = "CriticalMsg";
        break;
        case QtFatalMsg:
        text = "Fatal:";
        break;
    }
    QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString current_date = QString("(%1)").arg(current_date_time);
    QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date);
    QByteArray array = message.toLocal8Bit();
    char *p = array.data();
    for(int i = 0; i < array.count(); i++)
    {
        cout<<p[i];
    }
    cout<<endl;
    QFile file("/opt/test/log.txt");
    file.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << "\n";
    file.flush();
    file.close();
    mutex.unlock();
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qInstallMessageHandler(logOutput);
    qDebug()<<"Start";
    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(utf8);
    qDebug()<<__FUNCTION__<<"CurrentThread"<<QThread::currentThread();
    MainWorkFlow mainwork;
//    mainwork.moveToThread(&g_Thread);
//    g_Thread.start();
    return a.exec();
}
