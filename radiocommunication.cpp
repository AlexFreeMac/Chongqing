#include "radiocommunication.h"
#include <globalVariable.h>
#include "QDebug"
#include <QString>
#include <QThread>
RadioCommunication::RadioCommunication(QObject *parent) :
    QObject(parent)
{
    //qDebug()<<__FUNCTION__<<"CurrentThread"<<QThread::currentThread();
    connect(&timer,SIGNAL(timeout()),this,SLOT(timeoutSlot()));

    connect(this,SIGNAL(SendCMDRemoteCtrolOpenSignal()),this,SLOT(SendCMDRemoteCtrolOpen()));
    connect(this,SIGNAL(SendCMDRemoteCtrolCloseSignal()),this,SLOT(SendCMDRemoteCtrolClose()));
    connect(this,SIGNAL(SendCMDInjectionSignal(QString,short,int,int)),
            this,SLOT(SendCMDInjectionSlot(QString,short,int,int)));
    connect(this,SIGNAL(SendCMDChangeModeSignal(QString )),
                        this,SLOT(SendCMDChangeModeSlot(QString)));
    connect(this,SIGNAL(SendCMDChangeChannelSignal(int)),
            this,SLOT(SendCMDChangeChannelSlot(int)));
    connect(this,SIGNAL(SendCMDChangeTxSignal(int)),
            this,SLOT(SendCMDChangeTxSlot(int)));
    connect(this,SIGNAL(SendCMDChangeRxSignal(int)),
            this,SLOT(SendCMDChangeRxSlot(int)));
    connect(this,SIGNAL(SendCMDChangePowSignal(QString)),
            this,SLOT(SendCMDChangePowSlot(QString)));
    connect(this,SIGNAL(SendCMDChangeDSCEmitDataTypeSignal(int)),
            this,SLOT(SendCMDChangeDSCEmitDataTypeSlot(int)));
    connect(this,SIGNAL(SendCMDChangeATTSignal(int)),
            this,SLOT(SendCMDChangeATTSlot(int)));
    connect(this,SIGNAL(SendCMDChangeAGCAndMGCSignal(QString ,int )),
            this,SLOT(SendCMDChangeAGCAndMGCSlot(QString ,int )));
    connect(this,SIGNAL(SendCMDChangeSQLSignal(bool,int)),
            this,SLOT(SendCMDChangeSQLSlot(bool,int)));
    connect(this,SIGNAL(SendCMDChangeSilenceSignal(bool)),
            this,SLOT(SendCMDChangeSilenceSlot(bool)));
    connect(this,SIGNAL(SendCMDQueryPOWTrimSignal(QString)),
            this,SLOT(SendCMDQueryPOWTrimSlot(QString)));
    connect(this,SIGNAL(SendCMDChangeTuneModeSignal(bool)),
            this,SLOT(SendCMDChangeTuneModeSlot(bool)));
    connect(this,SIGNAL(SendCMDQuerySelfCheckSignal()),
            this,SLOT(SendCMDQuerySelfCheckSlot()));
    connect(this,SIGNAL(SendCMDQueryHostInfoSignal()),
            this,SLOT(SendCMDQueryHostInfoSlot()));
    connect(this,SIGNAL(SendCMDQueryStatusSignal()),
            this,SLOT(SendCMDQueryStatusSlot()));
    connect(this,SIGNAL(SendCMDTuneDebugModeStateSignal(bool)),
            this,SLOT(SendCMDTuneDebugModeStateSlot(bool)));
    connect(this,SIGNAL(SendCMDSystemQuerySignal()),
            this,SLOT(SendCMDSystemQuerySlot()));
    connect(this,SIGNAL(SendCMDPTTSettingSignal(int)),
            this,SLOT(SendCMDPTTSettingSlot(int)));
    connect(this,SIGNAL(SendCMDChannelStateQuerySignal()),
            this,SLOT(SendCMDChannelStateQuerySlot()));
    connect(this,SIGNAL(SendMainStationStateSettingSignal(QString , QString , int /*RaidoRF-ATT*/,
                                                          QString ,/**/int , bool , int ,
                                                          bool , int )),
            this,SLOT(SendMainStationStateSettingSlot(QString , QString , int /*RaidoRF-ATT*/,
                                                        QString ,/**/int , bool , int ,
                                                        bool , int )));
    connect(this,SIGNAL(SendCMDChannelEmitQuerySignal()),
            this,SLOT(SendCMDChannelEmitQuerySlot()));
    timer.start(1000*60*5);
    //timer.setSingleShot(true);
    //SendCMDManualtuneSlot();
}
void RadioCommunication::SendCMDManualtuneSlot()
{

    QByteArray array;
    unsigned char data[9];
    data[0] = 0x7E;
    data[1] = 0x7E;

    data[2] = 0x00;
    data[3] = 0x05;

    data[4] = 0x00;
    data[5] = 0x01;
    data[6] = 0x01;
    unsigned int checksum = 0;
    for(int i = 2; i < 7; i++)
    {
        checksum += data[i];
    }
    data[7] = (checksum>>8)&0xff;
    data[8] = checksum&0xff;
    for(int i = 0; i < 9 ;i++)
    {
        array.append(data[i]);
    }


    qDebug()<<array.length();
    QHostAddress address;
    address.setAddress(g_strRadioStationIP);
    if(g_isUseSerial)
    {

    }
    else
    {
        emit SendCMDManualtuneSignal(array, address, g_RadioStationUdpPort);
    }
}

void RadioCommunication::SendCMDRemoteCtrolOpen()
{
    QByteArray array;
    unsigned char data[10];
    data[0] = 0x7E;
    data[1] = 0x7E;

    data[2] = 0x00;
    data[3] = 0x06;

    data[4] = 0x00;
    data[5] = 0x01;
    data[6] = 0x6c;
    data[7] = 0x80;
    unsigned int checksum = 0;
    for(int i = 2; i < 8; i++)
    {
        checksum += data[i];
    }
    data[8] = (checksum>>8)&0xff;
    data[9] = checksum&0xff;
    for(int i = 0; i < 10 ;i++)
    {
        array.append(data[i]);
    }
    qDebug()<<__FUNCTION__<<array.length();
    QHostAddress address;
    address.setAddress(g_strRadioStationIP);
    if(g_isUseSerial)
    {
        emit SerialSendCMDRemoteCtrolOpenSignal(array);
    }
    else
    {
        emit SendCMDRemoteCtrolOpenSignal(array, address, g_RadioStationUdpPort);
    }
}

void RadioCommunication::SendCMDRemoteCtrolClose()
{
    QByteArray array;
    unsigned char data[10];
    data[0] = 0x7E;
    data[1] = 0x7E;

    data[2] = 0x00;
    data[3] = 0x06;

    data[4] = 0x00;
    data[5] = 0x01;
    data[6] = 0x6c;
    data[7] = 0x00;
    unsigned int checksum = 0;
    for(int i = 2; i < 8; i++)
    {
        checksum += data[i];
    }
    data[8] = (checksum>>8)&0xff;
    data[9] = checksum&0xff;
    for(int i = 0; i < 10 ;i++)
    {
        array.append(data[i]);
    }
    qDebug()<<__FUNCTION__<<array.length();
    QHostAddress address;
    address.setAddress(g_strRadioStationIP);
    if(g_isUseSerial)
    {

    }
    else
    {
        emit SendCMDRemoteCtrolCloseSignal(array, address, g_RadioStationUdpPort);
    }
}

void RadioCommunication::SendCMDInjectionSlot(QString mode, short channel, int rx, int tx)
{
        QByteArray array;
        int bufflen = 20;
        unsigned char data[bufflen];
        data[0] = 0x7E;
        data[1] = 0x7E;//header

        data[2] = 0x00;
        data[3] = 0x10;//len

        data[4] = 0x00;//source
        data[5] = 0x01;//destination
        data[6] = 0x02;//code
        if(mode == "SSB")
        {
            data[7] = 0x01<<5;
        }
        else if(mode == "DSC")
        {
            data[7] = 0x01<<6;
        }
        else if(mode == "AM")
        {
            data[7] = 0x03<<5;
        }
        else if(mode == "NBDP")
        {
            data[7] = 0x01<<7;
        }
        data[8] = (channel>>8)&0xff;
        data[9] = channel&0xff;

        data[10] = (rx>>24)&0xff;
        data[11] = (rx>>16)&0xff;
        data[12] = (rx>>8)&0xff;
        data[13] = rx&0xff;

        data[14] = (tx>>24)&0xff;
        data[15] = (tx>>16)&0xff;
        data[16] = (tx>>8)&0xff;
        data[17] = tx&0xff;

        unsigned int checksum = 0;
        for(int i = 2; i < 18; i++)
        {
            checksum += data[i];
        }
        data[18] = (checksum>>8)&0xff;
        data[19] = checksum&0xff;
        for(int i = 0; i < bufflen ;i++)
        {
            array.append(data[i]);
        }
        qDebug()<<__FUNCTION__<<array.length();
        QHostAddress address;
        address.setAddress(g_strRadioStationIP);
        //qDebug()<<__FUNCTION__<<__LINE__;
        for(int i = 0; i < 20; i++)
        {
            printf("0X%02X ", data[i]);
        }
        printf("\n");
        if(g_isUseSerial)
        {
            emit SerialSendCMDInjectionSignal(array);
        }
        else
        {
            emit SendCMDInjectionSignal(array, address, g_RadioStationUdpPort);
        }
}

void RadioCommunication::SendCMDChangeModeSlot(QString mode)
{
    QByteArray array;
    int bufflen = 10;
    unsigned char data[bufflen];
    data[0] = 0x7E;
    data[1] = 0x7E;//header

    data[2] = 0x00;
    data[3] = 0x06;//len

    data[4] = 0x00;//source
    data[5] = 0x01;//destination
    data[6] = 0x03;//code
    if(mode == "SSB")
    {
        data[7] = 0x01<<5;
    }
    else if(mode == "DSC")
    {
        data[7] = 0x01<<6;
    }
    else if(mode == "AM")
    {
        data[7] = 0x03<<5;
    }
    else if(mode == "NBDP")
    {
        data[7] = 0x01<<7;
    }
    unsigned int checksum = 0;
    for(int i = 2; i < 8; i++)
    {
        checksum += data[i];
    }
    data[8] = (checksum>>8)&0xff;
    data[9] = checksum&0xff;
    for(int i = 0; i < bufflen ;i++)
    {
        array.append(data[i]);
    }
    qDebug()<<__FUNCTION__<<array.length();
    QHostAddress address;
    address.setAddress(g_strRadioStationIP);
    if(g_isUseSerial)
    {

    }
    else
    {
        emit SendCMDChangeModeSignal(array, address, g_RadioStationUdpPort);
    }
}

void RadioCommunication::SendCMDChangeChannelSlot(int channel)
{
    QByteArray array;
    int bufflen = 11;
    unsigned char data[bufflen];
    data[0] = 0x7E;
    data[1] = 0x7E;//header

    data[2] = 0x00;
    data[3] = 0x07;//len

    data[4] = 0x00;//source
    data[5] = 0x01;//destination
    data[6] = 0x04;//code

    data[7] = (channel>>8)&0xff;
    data[8] = channel&0xff;

    unsigned int checksum = 0;
    for(int i = 2; i < 9; i++)
    {
        checksum += data[i];
    }
    data[9] = (checksum>>8)&0xff;
    data[10] = checksum&0xff;
    for(int i = 0; i < bufflen ;i++)
    {
        array.append(data[i]);
    }
    qDebug()<<__FUNCTION__<<array.length();
    QHostAddress address;
    address.setAddress(g_strRadioStationIP);
    if(g_isUseSerial)
    {

    }
    else
    {
        emit SendCMDChangeChannelSignal(array, address, g_RadioStationUdpPort);
    }
}

void RadioCommunication::SendCMDChangeTxSlot(int tx)
{
    QByteArray array;
    int bufflen = 13;
    unsigned char data[bufflen];
    data[0] = 0x7E;
    data[1] = 0x7E;//header

    data[2] = 0x00;
    data[3] = 0x09;//len

    data[4] = 0x00;//source
    data[5] = 0x01;//destination
    data[6] = 0x0b;//code

    data[7] = (tx>>24)&0xff;
    data[8] = (tx>>16)&0xff;
    data[9] = (tx>>8)&0xff;
    data[10] = tx&0xff;

    unsigned int checksum = 0;
    for(int i = 2; i < 11; i++)
    {
        checksum += data[i];
    }
    data[11] = (checksum>>8)&0xff;
    data[12] = checksum&0xff;
    for(int i = 0; i < bufflen ;i++)
    {
        array.append(data[i]);
    }
    qDebug()<<__FUNCTION__<<array.length();
    QHostAddress address;
    address.setAddress(g_strRadioStationIP);
    if(g_isUseSerial)
    {

    }
    else
    {
        emit SendCMDChangeTxSignal(array, address, g_RadioStationUdpPort);
    }
}

void RadioCommunication::SendCMDChangeRxSlot(int rx)
{
    QByteArray array;
    int bufflen = 13;
    unsigned char data[bufflen];
    data[0] = 0x7E;
    data[1] = 0x7E;//header

    data[2] = 0x00;
    data[3] = 0x09;//len

    data[4] = 0x00;//source
    data[5] = 0x01;//destination
    data[6] = 0x0c;//code

    data[7] = (rx>>24)&0xff;
    data[8] = (rx>>16)&0xff;
    data[9] = (rx>>8)&0xff;
    data[10] = rx&0xff;

    unsigned int checksum = 0;
    for(int i = 2; i < 11; i++)
    {
        checksum += data[i];
    }
    data[11] = (checksum>>8)&0xff;
    data[12] = checksum&0xff;
    for(int i = 0; i < bufflen ;i++)
    {
        array.append(data[i]);
    }
    qDebug()<<__FUNCTION__<<array.length();
    QHostAddress address;
    address.setAddress(g_strRadioStationIP);
    if(g_isUseSerial)
    {

    }
    else
    {
        emit SendCMDChangeRxSignal(array, address, g_RadioStationUdpPort);
    }
}

void RadioCommunication::SendCMDChangePowSlot(QString value)
{
    QByteArray array;
    int bufflen = 10;
    unsigned char data[bufflen];
    data[0] = 0x7E;
    data[1] = 0x7E;//header

    data[2] = 0x00;
    data[3] = 0x06;//len

    data[4] = 0x00;//source
    data[5] = 0x01;//destination
    data[6] = 0x0e;//code

    if(value == "L")
    {
        data[7] = 0x01<<6;
    }
    else if(value == "M")
    {
        data[7] = 0x01<<7;
    }
    else if(value == "H")
    {
        data[7] = 0x03<<6;
    }
    unsigned int checksum = 0;
    for(int i = 2; i < 8; i++)
    {
        checksum += data[i];
    }
    data[8] = (checksum>>8)&0xff;
    data[9] = checksum&0xff;
    for(int i = 0; i < bufflen ;i++)
    {
        array.append(data[i]);
    }
    qDebug()<<__FUNCTION__<<array.length();
    QHostAddress address;
    address.setAddress(g_strRadioStationIP);
    if(g_isUseSerial)
    {

    }
    else
    {
        emit SendCMDChangePowSignal(array, address, g_RadioStationUdpPort);
    }
}

void RadioCommunication::SendCMDChangeDSCEmitDataTypeSlot(int value)
{
    QByteArray array;
    int bufflen = 10;
    unsigned char data[bufflen];
    data[0] = 0x7E;
    data[1] = 0x7E;//header

    data[2] = 0x00;
    data[3] = 0x06;//len

    data[4] = 0x00;//source
    data[5] = 0x01;//destination
    data[6] = 0x0f;//code

    if(value == 0)
    {
        data[7] = 0x00<<5;
    }
    else if(value == 1)
    {
        data[7] = 0x01<<5;
    }
    else if(value == 2)
    {
        data[7] = 0x01<<6;
    }
    else if(value == 3)
    {
        data[7] = 0x03<<5;
    }
    unsigned int checksum = 0;
    for(int i = 2; i < 8; i++)
    {
        checksum += data[i];
    }
    data[8] = (checksum>>8)&0xff;
    data[9] = checksum&0xff;
    for(int i = 0; i < bufflen ;i++)
    {
        array.append(data[i]);
    }
    qDebug()<<__FUNCTION__<<array.length();
    QHostAddress address;
    address.setAddress(g_strRadioStationIP);
    if(g_isUseSerial)
    {

    }
    else
    {
        emit SendCMDChangeDSCEmitDataTypeSignal(array, address, g_RadioStationUdpPort);
    }
}

void RadioCommunication::SendCMDChangeATTSlot(int value)
{
    QByteArray array;
    int bufflen = 10;
    unsigned char data[bufflen];
    data[0] = 0x7E;
    data[1] = 0x7E;//header

    data[2] = 0x00;
    data[3] = 0x06;//len

    data[4] = 0x00;//source
    data[5] = 0x01;//destination
    data[6] = 0x10;//code

    if(value == 0)
    {
        data[7] = 0x00<<6;
    }
    else if(value == 1)
    {
        data[7] = 0x01<<6;
    }
    else if(value == 2)
    {
        data[7] = 0x01<<7;
    }

    unsigned int checksum = 0;
    for(int i = 2; i < 8; i++)
    {
        checksum += data[i];
    }
    data[8] = (checksum>>8)&0xff;
    data[9] = checksum&0xff;
    for(int i = 0; i < bufflen ;i++)
    {
        array.append(data[i]);
    }
    qDebug()<<__FUNCTION__<<array.length();
    QHostAddress address;
    address.setAddress(g_strRadioStationIP);
    if(g_isUseSerial)
    {

    }
    else
    {
        emit SendCMDChangeATTSignal(array, address, g_RadioStationUdpPort);
    }
}

void RadioCommunication::SendCMDChangeAGCAndMGCSlot(QString mode, int value)
{
    QByteArray array;
    int bufflen = 10;
    unsigned char data[bufflen];
    data[0] = 0x7E;
    data[1] = 0x7E;//header

    data[2] = 0x00;
    data[3] = 0x06;//len

    data[4] = 0x00;//source
    data[5] = 0x01;//destination
    data[6] = 0x11;//code

    if(mode == "AGC")
    {
        data[7] = value;
        data[7] = data[7]|0x80;
    }
    else if(mode == "MGC")
    {
        data[7] = value;
        data[7] = data[7]&0x7F;
    }

    unsigned int checksum = 0;
    for(int i = 2; i < 8; i++)
    {
        checksum += data[i];
    }
    data[8] = (checksum>>8)&0xff;
    data[9] = checksum&0xff;
    for(int i = 0; i < bufflen ;i++)
    {
        array.append(data[i]);
    }
    qDebug()<<__FUNCTION__<<array.length();
    QHostAddress address;
    address.setAddress(g_strRadioStationIP);
    if(g_isUseSerial)
    {

    }
    else
    {
        emit SendCMDChangeAGCAndMGCSignal(array, address, g_RadioStationUdpPort);
    }
}

void RadioCommunication::SendCMDChangeSQLSlot(bool isopen, int value)
{
    QByteArray array;
    int bufflen = 10;
    unsigned char data[bufflen];
    data[0] = 0x7E;
    data[1] = 0x7E;//header

    data[2] = 0x00;
    data[3] = 0x06;//len

    data[4] = 0x00;//source
    data[5] = 0x01;//destination
    data[6] = 0x12;//code

    if(isopen)
    {
        data[7] = value;
        data[7] = data[7]|0x80;
    }
    else
    {
        data[7] =value;
        data[7] = data[7]&0x7F;
    }

    unsigned int checksum = 0;
    for(int i = 2; i < 8; i++)
    {
        checksum += data[i];
    }
    data[8] = (checksum>>8)&0xff;
    data[9] = checksum&0xff;
    for(int i = 0; i < bufflen ;i++)
    {
        array.append(data[i]);
    }
    qDebug()<<__FUNCTION__<<array.length();
    QHostAddress address;
    address.setAddress(g_strRadioStationIP);
    if(g_isUseSerial)
    {

    }
    else
    {
        emit SendCMDChangeSQLSignal(array, address, g_RadioStationUdpPort);
    }
}

void RadioCommunication::SendCMDChangeSilenceSlot(bool isopen)
{
    QByteArray array;
    int bufflen = 10;
    unsigned char data[bufflen];
    data[0] = 0x7E;
    data[1] = 0x7E;//header

    data[2] = 0x00;
    data[3] = 0x06;//len

    data[4] = 0x00;//source
    data[5] = 0x01;//destination
    data[6] = 0x18;//code
    data[7] = 0x00;
    if(isopen)
    {
        data[7] = data[7]|0x80;
    }
    else
    {
        data[7] = data[7]&0x7F;
    }

    unsigned int checksum = 0;
    for(int i = 2; i < 8; i++)
    {
        checksum += data[i];
    }
    data[8] = (checksum>>8)&0xff;
    data[9] = checksum&0xff;
    for(int i = 0; i < bufflen ;i++)
    {
        array.append(data[i]);
    }
    qDebug()<<__FUNCTION__<<array.length();
    QHostAddress address;
    address.setAddress(g_strRadioStationIP);
    if(g_isUseSerial)
    {

    }
    else
    {
        emit SendCMDChangeSilenceSignal(array, address, g_RadioStationUdpPort);
    }
}

void RadioCommunication::SendCMDQueryPOWTrimSlot(QString mode)
{
    QByteArray array;
    int bufflen = 10;
    unsigned char data[bufflen];
    data[0] = 0x7E;
    data[1] = 0x7E;//header

    data[2] = 0x00;
    data[3] = 0x06;//len

    data[4] = 0x00;//source
    data[5] = 0x01;//destination
    data[6] = 0x1a;//code
    data[7] = 0x00;
    if(mode == "SSB")
    {
        data[7] = 2;
    }
    else if(mode == "DSC")
    {
        data[7] = 3;
    }

    unsigned int checksum = 0;
    for(int i = 2; i < 8; i++)
    {
        checksum += data[i];
    }
    data[8] = (checksum>>8)&0xff;
    data[9] = checksum&0xff;
    for(int i = 0; i < bufflen ;i++)
    {
        array.append(data[i]);
    }
    qDebug()<<__FUNCTION__<<array.length();
    QHostAddress address;
    address.setAddress(g_strRadioStationIP);
    if(g_isUseSerial)
    {

    }
    else
    {
        emit SendCMDQueryPOWTrimSignal(array, address, g_RadioStationUdpPort);
    }
}

void RadioCommunication::SendCMDChangeTuneModeSlot(bool isManual)
{
    QByteArray array;
    int bufflen = 10;
    unsigned char data[bufflen];
    data[0] = 0x7E;
    data[1] = 0x7E;//header

    data[2] = 0x00;
    data[3] = 0x06;//len

    data[4] = 0x00;//source
    data[5] = 0x01;//destination
    data[6] = 0x1c;//code
    data[7] = 0x00;
    if(isManual)
    {
        data[7] = data[7]|0x80;
    }
    else
    {
        data[7] = data[7]&0x7F;
    }

    unsigned int checksum = 0;
    for(int i = 2; i < 8; i++)
    {
        checksum += data[i];
    }
    data[8] = (checksum>>8)&0xff;
    data[9] = checksum&0xff;
    for(int i = 0; i < bufflen ;i++)
    {
        array.append(data[i]);
    }
    qDebug()<<__FUNCTION__<<array.length();
    QHostAddress address;
    address.setAddress(g_strRadioStationIP);
    if(g_isUseSerial)
    {

    }
    else
    {
        emit SendCMDChangeTuneModeSignal(array, address, g_RadioStationUdpPort);
    }
}

void RadioCommunication::SendCMDQuerySelfCheckSlot()
{
    QByteArray array;
    int bufflen = 9;
    unsigned char data[bufflen];
    data[0] = 0x7E;
    data[1] = 0x7E;//header

    data[2] = 0x00;
    data[3] = 0x05;//len

    data[4] = 0x00;//source
    data[5] = 0x01;//destination
    data[6] = 0x66;//code

    unsigned int checksum = 0;
    for(int i = 2; i < 7; i++)
    {
        checksum += data[i];
    }
    data[7] = (checksum>>8)&0xff;
    data[8] = checksum&0xff;
    for(int i = 0; i < bufflen ;i++)
    {
        array.append(data[i]);
    }
    qDebug()<<__FUNCTION__<<array.length();
    QHostAddress address;
    address.setAddress(g_strRadioStationIP);
    if(g_isUseSerial)
    {

    }
    else
    {
        emit SendCMDQuerySelfCheckSignal(array, address, g_RadioStationUdpPort);
    }
}

void RadioCommunication::SendCMDQueryHostInfoSlot()
{
    QByteArray array;
    int bufflen = 9;
    unsigned char data[bufflen];
    data[0] = 0x7E;
    data[1] = 0x7E;//header

    data[2] = 0x00;
    data[3] = 0x05;//len

    data[4] = 0x00;//source
    data[5] = 0x01;//destination
    data[6] = 0x67;//code

    unsigned int checksum = 0;
    for(int i = 2; i < 7; i++)
    {
        checksum += data[i];
    }
    data[7] = (checksum>>8)&0xff;
    data[8] = checksum&0xff;
    for(int i = 0; i < bufflen ;i++)
    {
        array.append(data[i]);
    }
    qDebug()<<__FUNCTION__<<array.length();
    QHostAddress address;
    address.setAddress(g_strRadioStationIP);
    if(g_isUseSerial)
    {

    }
    else
    {
        emit SendCMDQueryHostInfoSignal(array, address, g_RadioStationUdpPort);
    }
}

void RadioCommunication::SendCMDQueryStatusSlot()
{
    QByteArray array;
    int bufflen = 9;
    unsigned char data[bufflen];
    data[0] = 0x7E;
    data[1] = 0x7E;//header

    data[2] = 0x00;
    data[3] = 0x05;//len

    data[4] = 0x00;//source
    data[5] = 0x01;//destination
    data[6] = 0x6a;//code

    unsigned int checksum = 0;
    for(int i = 2; i < 7; i++)
    {
        checksum += data[i];
    }
    data[7] = (checksum>>8)&0xff;
    data[8] = checksum&0xff;
    for(int i = 0; i < bufflen ;i++)
    {
        array.append(data[i]);
    }
    qDebug()<<__FUNCTION__<<array.length();
    QHostAddress address;
    address.setAddress(g_strRadioStationIP);
    if(g_isUseSerial)
    {

    }
    else
    {
        emit SendCMDQueryStatusSignal(array, address, g_RadioStationUdpPort);
    }
}

void RadioCommunication::SendCMDTuneDebugModeStateSlot(bool isOpen)
{
    QByteArray array;
    int bufflen = 10;
    unsigned char data[bufflen];
    data[0] = 0x7E;
    data[1] = 0x7E;//header

    data[2] = 0x00;
    data[3] = 0x06;//len

    data[4] = 0x00;//source
    data[5] = 0x01;//destination
    data[6] = 0x6b;//code
    data[7] = 0x00;
    if(isOpen)
    {
        data[7] = data[7]|0x40;
    }
    else
    {
        data[7] = data[7]&0x7F;
    }

    unsigned int checksum = 0;
    for(int i = 2; i < 8; i++)
    {
        checksum += data[i];
    }
    data[8] = (checksum>>8)&0xff;
    data[9] = checksum&0xff;
    for(int i = 0; i < bufflen ;i++)
    {
        array.append(data[i]);
    }
    qDebug()<<__FUNCTION__<<array.length();
    QHostAddress address;
    address.setAddress(g_strRadioStationIP);
    if(g_isUseSerial)
    {

    }
    else
    {
        emit SendCMDTuneDebugModeStateSignal(array, address, g_RadioStationUdpPort);
    }
}

void RadioCommunication::SendCMDSystemQuerySlot()
{
    QByteArray array;
    int bufflen = 9;
    unsigned char data[bufflen];
    data[0] = 0x7E;
    data[1] = 0x7E;//header

    data[2] = 0x00;
    data[3] = 0x05;//len

    data[4] = 0x00;//source
    data[5] = 0x01;//destination
    data[6] = 0x6E;//code

    unsigned int checksum = 0;
    for(int i = 2; i < 7; i++)
    {
        checksum += data[i];
    }
    data[7] = (checksum>>8)&0xff;
    data[8] = checksum&0xff;
    for(int i = 0; i < bufflen ;i++)
    {
        array.append(data[i]);
    }
    qDebug()<<__FUNCTION__<<array.length();
    QHostAddress address;
    address.setAddress(g_strRadioStationIP);
    if(g_isUseSerial)
    {

    }
    else
    {
        emit SendCMDSystemQuerySignal(array, address, g_RadioStationUdpPort);
    }
}

void RadioCommunication::SendCMDPTTSettingSlot(int state)
{
    QByteArray array;
    int bufflen = 10;
    unsigned char data[bufflen];
    data[0] = 0x7E;
    data[1] = 0x7E;//header

    data[2] = 0x00;
    data[3] = 0x06;//len

    data[4] = 0x00;//source
    data[5] = 0x01;//destination
    data[6] = 0x6f;//code
    data[7] = 0x00;
    if(state == 0x01)
    {
        data[7] = 0x01;
    }
    else
    {
        data[7] = 0x00;
    }

    unsigned int checksum = 0;
    for(int i = 2; i < 8; i++)
    {
        checksum += data[i];
    }
    data[8] = (checksum>>8)&0xff;
    data[9] = checksum&0xff;
    for(int i = 0; i < bufflen ;i++)
    {
        array.append(data[i]);
    }
    qDebug()<<__FUNCTION__<<array.length();
    QHostAddress address;
    address.setAddress(g_strRadioStationIP);
    if(g_isUseSerial)
    {
        SerialSendCMDPTTSettingSignal(array);
    }
    else
    {
        emit SendCMDPTTSettingSignal(array, address, g_RadioStationUdpPort);
    }
}

void RadioCommunication::SendCMDChannelStateQuerySlot()
{
    QByteArray array;
    int bufflen = 9;
    unsigned char data[bufflen];
    data[0] = 0x7E;
    data[1] = 0x7E;//header

    data[2] = 0x00;
    data[3] = 0x05;//len

    data[4] = 0x00;//source
    data[5] = 0x01;//destination
    data[6] = 0x73;//code

    unsigned int checksum = 0;
    for(int i = 2; i < 7; i++)
    {
        checksum += data[i];
    }
    data[7] = (checksum>>8)&0xff;
    data[8] = checksum&0xff;
    for(int i = 0; i < bufflen ;i++)
    {
        array.append(data[i]);
    }
    qDebug()<<__FUNCTION__<<array.length();
    QHostAddress address;
    address.setAddress(g_strRadioStationIP);
    if(g_isUseSerial)
    {

    }
    else
    {
        emit SendCMDChannelStateQuerySignal(array, address, g_RadioStationUdpPort);
    }
}

void RadioCommunication::SendMainStationStateSettingSlot(QString mode, QString sendRFvalue, int value,
                                                         QString AGCOrMGCmode, int AGCOrMGCvalue,
                                                         bool isSQLOpen, int SQLvalue,
                                                         bool tuneModeIsManual, int AntennaType)
{
    QByteArray array;
    int bufflen = 16;
    unsigned char data[bufflen];
    data[0] = 0x7E;
    data[1] = 0x7E;//header

    data[2] = 0x00;
    data[3] = 0x0c;//len

    data[4] = 0x00;//source
    data[5] = 0x01;//destination
    data[6] = 0x74;//code

    if(mode == "SSB")
    {
        data[7] = 0x01<<5;
    }
    else if(mode == "DSC")
    {
        data[7] = 0x01<<6;
    }
    else if(mode == "AM")
    {
        data[7] = 0x03<<5;
    }
    else if(mode == "NBDP")
    {
        data[7] = 0x01<<7;
    }
    if(sendRFvalue == "L")
    {
        data[8] = 0x01<<6;
    }
    else if(sendRFvalue == "M")
    {
        data[8] = 0x01<<7;
    }
    else if(sendRFvalue == "H")
    {
        data[8] = 0x03<<6;
    }
    if(value == 0)
    {
        data[9] = 0x00<<6;
    }
    else if(value == 1)
    {
        data[9] = 0x01<<6;
    }
    else if(value == 2)
    {
        data[9] = 0x01<<7;
    }
    if(AGCOrMGCmode == "AGC")
    {
        data[10] = AGCOrMGCvalue;
        data[10] = data[10]|0x80;
    }
    else if(AGCOrMGCmode == "MGC")
    {
        data[10] = AGCOrMGCvalue;
        data[10] = data[10]&0x7F;
    }
    if(isSQLOpen)
    {
        data[11] = SQLvalue;
        data[11] = data[11]|0x80;
    }
    else
    {
        data[11] =SQLvalue;
        data[11] = data[11]&0x7F;
    }
    if(tuneModeIsManual)
    {
        data[12] = 1;
    }
    else
    {
        data[12] = 0;
    }
    data[13] = AntennaType;
    unsigned int checksum = 0;
    for(int i = 2; i < 14; i++)
    {
        checksum += data[i];
    }
    data[14] = (checksum>>8)&0xff;
    data[15] = checksum&0xff;
    for(int i = 0; i < bufflen ;i++)
    {
        array.append(data[i]);
    }
    qDebug()<<__FUNCTION__<<array.length();
    QHostAddress address;
    address.setAddress(g_strRadioStationIP);
    if(g_isUseSerial)
    {

    }
    else
    {
        emit SendCMDChannelStateQuerySignal(array, address, g_RadioStationUdpPort);
    }
}

void RadioCommunication::SendCMDChannelEmitQuerySlot()
{
    QByteArray array;
    int bufflen = 11;
    unsigned char data[bufflen];
    data[0] = 0x7E;
    data[1] = 0x7E;//header

    data[2] = 0x00;
    data[3] = 0x07;//len

    data[4] = 0x00;//source
    data[5] = 0x01;//destination
    data[6] = 0x75;//code
    data[7] = 0x00;
    data[8] = 0x01;
    unsigned int checksum = 0;
    for(int i = 2; i < 9; i++)
    {
        checksum += data[i];
    }
    data[9] = (checksum>>8)&0xff;
    data[10] = checksum&0xff;
    for(int i = 0; i < bufflen ;i++)
    {
        array.append(data[i]);
    }
    qDebug()<<__FUNCTION__<<array.length();
    QHostAddress address;
    address.setAddress(g_strRadioStationIP);
    if(g_isUseSerial)
    {

    }
    else
    {
        emit SendCMDChannelEmitQuerySignal(array, address, g_RadioStationUdpPort);
    }
}

void RadioCommunication::timeoutSlot()
{
    //emit SendCMDRemoteCtrolOpenSignal();//"DSC", "H", 2,"MGC",3, false, 20,false, 1
//    emit SendCMDTuneDebugModeStateSignal(false);
//    emit SendCMDChangeTuneModeSignal(false);
//    emit SendCMDChangeAGCAndMGCSlot(2);
    //emit SendCMDChangeATTSignal(3);
    SendCMDRemoteCtrolOpen();
    SendCMDQueryStatusSlot();
}

void RadioCommunication::receiverRadioInfo( char *buff, int len)
{
    qDebug()<<"len:"<<len;
    unsigned int checksum = 0;
    for(int i = 0 ; i < len;i++)
    {
        printf("%02x ",(unsigned char)buff[i]);
        if(i > 1 && i < len-2)
        {
            checksum += (unsigned char)buff[i];
        }
    }
    printf("\n");
    printf("checksum 0x%04x,0x%02x 0x%02x\n",checksum, (unsigned char)buff[len-2], (unsigned char)buff[len-1]);
    if((((checksum>>8)&0xff) == (unsigned char)buff[len-2]) && ((checksum & 0xff) == (unsigned char)buff[len-1]) )
    //if(1)
    {
        if(buff[0] == 0x7E && buff[1] == 0x7E)
        {
            switch(buff[6])
            {
            case REMOTE_CONTROL_CMD_CODE:
                qDebug()<<"Remote Control OK";
                break;
            case MANUAL_TUNE_CMD_CODE:
                qDebug()<<"Manualtune OK";
                break;
            case TUNE_REPORT_CMD_CODE:
                {
                    qDebug()<<"Tune report";
                    unsigned char bit5 = ((unsigned char)buff[11]>>5)&0x01;
                    unsigned char bit4 = ((unsigned char)buff[11]>>4)&0x01;
                    unsigned char bit3 = ((unsigned char)buff[11]>>3)&0x01;
                    if(bit3 == 0x01)
                    {
                        qDebug()<<"tune mode: Manual tune";
                    }
                    else
                    {
                        qDebug()<<"tune mode: Auto tune";
                    }
                    if(bit4 == 0x01)
                    {
                        qDebug()<<"tune  success";
                        emit TuneSuccessSignal();
                    }
                    else
                    {
                        qDebug()<<"tune  fail";
                        emit TuneFailSignal();
                    }
                    if(bit5 == 0x01)
                    {
                        qDebug()<<"tune start";
                    }
                    else
                    {
                        qDebug()<<"tune stop";
                    }
                }
                break;
            case STATUS_QUERY_CMD_CODE:
            {
                qDebug()<<__LINE__<<STATUS_QUERY_CMD_CODE;
                int gps[9];
                int index = 0;
                for(int i = 17; i < 26; i++)
                {
                    printf("%d ",(unsigned char)buff[i]);
                    gps[index++] = buff[i];
                }
                printf("\n");
                QString coordinateStr;
                if(gps[0]/10%10 == 0)
                {
                    coordinateStr = "NE";
                }
                if(gps[0]/10%10 == 1)
                {
                    coordinateStr = "NW";
                }
                if(gps[0]/10%10 == 2)
                {
                    coordinateStr = "SE";
                }
                if(gps[0]/10%10 == 3)
                {
                    coordinateStr = "SW";
                }
                QString gpsStr;
                gpsStr = QString::number(gps[0]%10)+
                        QString::number(gps[1]/10%10)+
                        QString::number(gps[1]%10)+
                        QString::number(gps[2]/10%10)+
                        QString::number(gps[2]%10)+
                        QString::number(gps[3]/10%10)+
                        QString::number(gps[3]%10)+
                        QString::number(gps[4]/10%10)+
                        QString::number(gps[4]%10)+
                        QString::number(gps[5]/10%10)+
                        QString::number(gps[5]%10)+
                        QString::number(gps[6]/10%10)+
                        QString::number(gps[6]%10)+
                        QString::number(gps[7]/10%10)+
                        QString::number(gps[7]%10)+
                        QString::number(gps[8]/10%10)+
                        QString::number(gps[8]%10);
                QString latitudeStr = gpsStr.left(8).insert(2,'.');//jing
                QString longitudeStr= gpsStr.right(9);//
                longitudeStr = longitudeStr.insert(3,'.');
                int h = buff[26];
                int m = buff[27];
                QString utcString = QString::number(h)+":"+QString::number(m);
                qDebug()<<"coordinateStr"<<coordinateStr<<"gps:"<<gpsStr
                          <<"longitudeStr"<<longitudeStr
                          <<"latitudeStr"<<latitudeStr
                          <<"UTC"<<utcString;

                emit SendGPSInfo(coordinateStr,longitudeStr, latitudeStr, utcString);
            }
                break;
            case ERROR_CMD_CODE:
                qDebug()<<"CMD error";
            default:
                break;
            }
        }
        else
        {
            qDebug()<<__FUNCTION__<<"Header error!!";
        }
    }
    else
    {
        qDebug()<<__FUNCTION__<<"Checksum error!!";
    }
}




