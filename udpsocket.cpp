#include "udpsocket.h"
#include "globalVariable.h"
#include <stdio.h>
UdpSocket::UdpSocket()
{
}

void UdpSocket::run()
{
    m_psocket = new QUdpSocket();
    qDebug()<<__FILE__<<__FUNCTION__<<"CurrentThread"<<QThread::currentThread();
    bool res = m_psocket->bind(QHostAddress::Any,g_LocalUdpPort);
    qDebug()<<"BindState:"<<res<<g_LocalUdpPort;
    connect(m_psocket,SIGNAL(readyRead()),this,SLOT(readMessages()),Qt::DirectConnection);
    connect(m_psocket,SIGNAL(destroyed()),m_psocket,SLOT(deleteLater()),Qt::DirectConnection);
    exec();
}

void UdpSocket::readMessages()
{
    char tmpBuff[4096];
    QHostAddress host;
    quint16 port;
    int c = m_psocket->readDatagram(tmpBuff, 4096, &host, &port);
    qDebug()<<__FUNCTION__<<"count:"<<c<<"IP:"<<host.toString()<<"Port:"<<port<<QThread::currentThread();
    if(port == g_RadioStationUdpPort/* && host.toString() == g_strRadioStationIP*/)
    {
        emit RadioCommunicationSignal(tmpBuff,c);
    }
    if(port == g_TransportUdpPort/* && host.toString() == g_strTransforIP*/)
    {
        emit StransforLayerCommunication(tmpBuff,c);
    }
    if(port == g_GetFreqUdpPort/* && host.toString() == g_strGetFreqUdpIP*/)
    {
//        QueryFreqData data ;
//        memcpy(&data, (QueryFreqData*)tmpBuff,sizeof(data));
//        qDebug()<<data.time<<data.tx1;
        qDebug()<<__FUNCTION__<<"g_GetFreqUdpPort:"<<g_GetFreqUdpPort;
        emit ReplyofQueryFreqSignal(tmpBuff,c);
        //emit writeshiftToRadioMessagesSignal();
    }
}

void UdpSocket::sendMessages(QByteArray &byteArray, QHostAddress &address, quint16 port)
{
    int c = m_psocket->writeDatagram(byteArray, address, port);
    qDebug()<<__FUNCTION__<<"Len:"<<c<<QThread::currentThread();
//    for(int i = 0 ; i < byteArray.length();i++)
//    {
//        printf("%02x ",(unsigned char)byteArray.at(i));
//    }
//    printf("\n");
}
