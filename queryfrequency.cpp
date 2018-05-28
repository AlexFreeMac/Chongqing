#include "queryfrequency.h"
#include "globalVariable.h"
#include "QTime"
#include "QDebug"
#include <QThread>
QueryFrequency::QueryFrequency(QObject *parent) :
    QObject(parent)
{
    connect(&getFreqTimer,SIGNAL(timeout()),this,SLOT(OntimerToGetFreq()));
    getFreqTimer.start(1000*60);
}

void QueryFrequency::needQueryFreq()
{
    QTime time;
    time = QTime::currentTime();
    QString strtime = time.toString("hhmm");
    qDebug()<<strtime;
    QByteArray tmpByteArray = strtime.toLatin1();
    QHostAddress address;
    address.setAddress(g_strGetFreqUdpIP);
    qDebug()<<__FUNCTION__<<"CurrentThread"<<QThread::currentThread();
    emit queryFreqSignal(tmpByteArray,address,g_GetFreqUdpPort);
}

void QueryFrequency::OntimerToGetFreq()
{
    QTime time;
    time = QTime::currentTime();
    QString strtime = time.toString("hhmm");
    qDebug()<<strtime;
    QByteArray tmpByteArray = strtime.toLatin1();
    QHostAddress address;
    address.setAddress(g_strGetFreqUdpIP);
    qDebug()<<__FUNCTION__<<"CurrentThread"<<QThread::currentThread();
    emit queryFreqSignal(tmpByteArray,address,g_GetFreqUdpPort);
}
