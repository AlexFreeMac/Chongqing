#include "readconfigfile.h"
#include "QCoreApplication"
#include <QString>
#include <QSettings>
#include <QDebug>
#include "globalVariable.h"
ReadConfigFile::ReadConfigFile(QObject *parent) :
    QObject(parent)
{
    QString dir = QCoreApplication::applicationDirPath();
    QString iniFilePath = dir+"/config.ini";
    qDebug()<<"Current Dir:"<<iniFilePath;
    QSettings *configIniRead = new QSettings(iniFilePath, QSettings::IniFormat);
    QString strRadioStationIP = configIniRead->value("/IP/RadioStationIP").toString();
    QString strLocalIP = configIniRead->value("/IP/LocalIP").toString();
    QString strPhysicalIP = configIniRead->value("/IP/PhysicalIP").toString();
    QString strGetFreqUdpIP = configIniRead->value("IP/GetFreqUdpIP").toString();
    QString strTransforIP = configIniRead->value("/IP/TransforIP").toString();

    quint16 RadioStationUdpPort = configIniRead->value("/PORT/RadioStationUdpPort").toUInt();
    quint16 PhysicalUdpPort = configIniRead->value("/PORT/PhysicalUdpPort").toUInt();
    quint16 LocalUdpPort = configIniRead->value("/PORT/LocalUdpPort").toUInt();
    quint16 GetFreqUdpPort = configIniRead->value("/PORT/GetFreqUdpPort").toUInt();
    quint16 TransportUdpPort = configIniRead->value("/PORT/TransportUdpPort").toUInt();

    g_TransportUdpPort = TransportUdpPort;
    g_strTransforIP = strTransforIP;
    g_LocalUdpPort = LocalUdpPort;
    g_strLocalIP = strLocalIP;
    qDebug()<<"RadioStationUdpPort:"<<RadioStationUdpPort<<"strRadioStationIP:"<<strRadioStationIP;
    qDebug()<<"PhysicalUdpPort"<<PhysicalUdpPort<<"strPhysicalIP:"<<strPhysicalIP;
    qDebug()<<"LocalUdpPort:"<<LocalUdpPort<<"strLocalIP:"<<strLocalIP;
    qDebug()<<"GetFreqUdpPort"<<GetFreqUdpPort<<"strGetFreqUdpIP:"<<strGetFreqUdpIP;
    qDebug()<<"TransportUdpPort"<<TransportUdpPort<<"strTransforIP:"<<strTransforIP;
}
