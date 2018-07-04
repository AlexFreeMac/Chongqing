#include "serialport.h"
#include "QDebug"
#include "stdio.h"
#include "globalVariable.h"
SerialPort::SerialPort(QObject *parent) :
    QThread(parent)
{
    m_pSerial = NULL;
}

QSerialPort *SerialPort::GetSerial()
{
    return m_pSerial;
}

void SerialPort::run()
{
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
            m_pSerial->setBaudRate(QSerialPort::Baud19200);
            m_pSerial->setDataBits(QSerialPort::Data8);
            m_pSerial->setStopBits(QSerialPort::OneStop);
            m_pSerial->setParity(QSerialPort::NoParity);
            qDebug()<<"Bind read "<<connect(m_pSerial,SIGNAL(readyRead()),this,SLOT(readMessages()),Qt::DirectConnection);
            qDebug()<<"Bind Delete "<<connect(m_pSerial,SIGNAL(destroyed()),m_pSerial,SLOT(deleteLater()),Qt::DirectConnection);
        }
        else
        {
            qDebug()<<"Open Serial Device fail"<<m_pSerial->errorString();
        }
    }
    exec();
}

void SerialPort::readMessages()
{
    char buff[4096];
    int c = m_pSerial->read(buff,4096);
    //qDebug()<<__FUNCTION__<<"Len"<<c<<QThread::currentThread();
    for(int i = 0; i < c; i++)
    {
        //printf("0X%02X ",(unsigned char)buff[i]);
        g_freeBytes.acquire();
        g_BUFF[g_WriteIndex++] = buff[i];
        if(g_WriteIndex == 1024)
        {
            g_WriteIndex = 0;
        }
        g_usedBytes.release();
    }
    printf("\n");
    //qDebug()<<"G_BUFF LEN:"<<g_usedBytes.available();
    //emit getShifResultSignal(buff,c);
}

void SerialPort::writeMessages(char *buff, int len)
{
    /*int c = */m_pSerial->write(buff,len);


    //qDebug()<<__FUNCTION__<<"Len"<<c<<QThread::currentThread();
}

void SerialPort::writeMessages(QByteArray &array)
{
    qDebug()<<__FUNCTION__<<"Start Serial";
    int c = m_pSerial->write(array);
    qDebug()<<__FUNCTION__<<"Len"<<c;
}
