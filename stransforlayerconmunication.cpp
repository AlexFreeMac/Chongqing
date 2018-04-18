#include "stransforlayerconmunication.h"
#include "globalVariable.h"
#include "QDebug"
StransforLayerConmunication::StransforLayerConmunication(QObject *parent) :
    QObject(parent)
{
    m_pStransforLayerSocket = new QUdpSocket();
    QHostAddress localAddress;
    localAddress.setAddress(g_strLocalIP);
    m_pStransforLayerSocket->bind(localAddress,g_LocalUdpPort);
    connect(m_pStransforLayerSocket,SIGNAL(readyRead()),this,SLOT(readMessages()));
    connect(&m_SendTimer,SIGNAL(timeout()),this,SLOT(sendMessages()));
    m_SendTimer.start(2000);
}

void StransforLayerConmunication::readMessages()
{
    char tmpbuff[4096];
    QHostAddress remoteIp;
    quint16 remotePort;
    m_pStransforLayerSocket->readDatagram(tmpbuff,4096,&remoteIp,&remotePort);
    qDebug()<<"remoteIp"<<remoteIp.toString()<<"remotePort:"<<remotePort<<"buff:"<<tmpbuff;
}

void StransforLayerConmunication::sendMessages()
{
    QString test="qiuhong,qiuhong";
    QByteArray cstr = test.toLatin1();
    QHostAddress TransforAddress;
    TransforAddress.setAddress(g_strTransforIP);
    m_pStransforLayerSocket->writeDatagram(cstr,TransforAddress,g_TransportUdpPort);
    //qDebug()<<test;
}
