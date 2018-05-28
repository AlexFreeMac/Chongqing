#include "serialport.h"
#include "QDebug"
#include "stdio.h"
SerialPort::SerialPort(QObject *parent) :
    QThread(parent)
{
}

void SerialPort::run()
{
    QSerialPortInfo *pSerialInfo;
    pSerialInfo = new QSerialPortInfo();
    QList<QSerialPortInfo> serialPortList;
    serialPortList = pSerialInfo->availablePorts();
    if(serialPortList.count() > 0)
    {
        QSerialPortInfo neadOpenPortInfo = serialPortList.at(0);
        for(int i = 0; i < serialPortList.count(); i++)
        {
            qDebug()<<serialPortList.at(i).portName()<<serialPortList.at(i).description();
            if(serialPortList.at(i).portName() == "ttyS4")//com1
            {
                neadOpenPortInfo = serialPortList.at(i);
            }
        }
        m_pSerial = new QSerialPort();
        qDebug()<<neadOpenPortInfo.portName();
        m_pSerial->setPort(neadOpenPortInfo);
        if(m_pSerial->open(QIODevice::ReadWrite))
        {
            qDebug()<<"Open Serial Device OK"<<QThread::currentThread();
            m_pSerial->setBaudRate(QSerialPort::Baud115200);
            m_pSerial->setDataBits(QSerialPort::Data8);
            m_pSerial->setStopBits(QSerialPort::OneStop);
            m_pSerial->setParity(QSerialPort::NoParity);
            connect(m_pSerial,SIGNAL(readyRead()),this,SLOT(readMessages()),Qt::DirectConnection);
            connect(m_pSerial,SIGNAL(destroyed()),m_pSerial,SLOT(deleteLater()),Qt::DirectConnection);
            exec();
        }
        else
        {
            qDebug()<<"Open Serial Device fail"<<m_pSerial->errorString();
        }
    }
}

void SerialPort::readMessages()
{
    char buff[4096];
    int c = m_pSerial->read(buff,4096);
    qDebug()<<__FILE__<<__FUNCTION__<<"Len"<<c<<QThread::currentThread();
    for(int i = 0; i < c; i++)
    {
        printf("\n0X%02X \n",(unsigned char)buff[i]);
    }
    emit getShifResultSignal(buff,c);
}

void SerialPort::writeMessages(char *buff, int len)
{
    int c = m_pSerial->write(buff,len);
    qDebug()<<__FILE__<<__FUNCTION__<<"Len"<<c<<QThread::currentThread();
}
