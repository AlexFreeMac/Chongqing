#include "mainworkflow.h"
#include "qmetatype.h"
#include "QTime"
MainWorkFlow::MainWorkFlow(QObject *parent) :
    QObject(parent)
{
    qDebug()<<" MainWorkFlow CurrentThread"<<QThread::currentThread();

    isNeedSendMessages = false;
    isGetChannels = false;
    isSendGetChannels = false;

    isTimeout = false;
    isTuneOK = false;
    isSendOK = false;
    isShiftRadioOk = false;
    isSendShiftAntenna = false;
    readConfig = new ReadConfigFile();
    m_pUdpThread = new UdpSocket();
    m_pUdpThread->start();
    m_pSerialPortThread = new SerialPort();
    m_pSerialPortThread->start();
//    m_pSerialPortThread->moveToThread(m_pUdpThread->currentThread());
    m_pSerialDataDealThread = new SerialRadioDataDeal();
    m_pSerialDataDealThread->start();

    m_pShiftAntenna = new ShiftAntenna();
    m_pShiftAntenna->moveToThread(&m_ShiftAntennaThread);
    m_ShiftAntennaThread.start();

    m_StransforLayerCommunication = new StransforLayerCommunication();
    m_StransforLayerCommunication->moveToThread(&m_StransforLayerCommunicationThread);
    m_StransforLayerCommunicationThread.start();

    m_pRadioCommunication = new RadioCommunication();
    m_pRadioCommunication->moveToThread(&m_RadioCommunicationThread);
    m_RadioCommunicationThread.start();

    m_pQueryFreq = new QueryFrequency();

    m_physicallayer = new PhysicalLayerCommunication();
    m_physicallayer->moveToThread(&m_physicallayerThread);
    m_physicallayerThread.start();
    //qRegisterMetaType<QHostAddress>("QHostAddress");
    //----------serial-------------

    //----------serial-------------
    //
    connect(m_pQueryFreq,SIGNAL(queryFreqSignal(QByteArray&, QHostAddress&,quint16)),
            m_pUdpThread,SLOT(sendMessages(QByteArray&, QHostAddress&,quint16)),Qt::DirectConnection);
    //stransform--->udp
    connect(m_StransforLayerCommunication,SIGNAL(sendMessageSignal(QByteArray&, QHostAddress&,quint16)),
            m_pUdpThread,SLOT(sendMessages(QByteArray&, QHostAddress&,quint16)),Qt::DirectConnection);
    //stransform--->PHY
//    connect(m_StransforLayerCommunication,SIGNAL(sendUserMessagesSignal(char*,int)),
//            m_physicallayer,SLOT(encodeSlot(char*,int)));
    //stransform--->this
    connect(m_StransforLayerCommunication,SIGNAL(sendUserMessagesSignal(char *,int, char * ,int)),
            this,SLOT(needSendMessagesToPhysical(char *,int, char * ,int)));
    //this--->queryFreq
    connect(this,SIGNAL(needQueryFreqSignal()),m_pQueryFreq,SLOT(needQueryFreq()),Qt::DirectConnection);
    //PHY-->>stransform
//    connect(m_physicallayer,SIGNAL(SendMessageStatus(char* , int ,int ,int)),
//            m_StransforLayerCommunication,SLOT(SendMessagesState(char* , int ,int ,int)));
    //RadioCtrol
    connect(m_pRadioCommunication,SIGNAL(SendCMDManualtuneSignal(QByteArray&,QHostAddress&,quint16)),
            m_pUdpThread,SLOT(sendMessages(QByteArray&,QHostAddress&,quint16)),Qt::DirectConnection);
    connect(m_pRadioCommunication,SIGNAL(SendCMDRemoteCtrolOpenSignal(QByteArray&,QHostAddress&,quint16)),
            m_pUdpThread,SLOT(sendMessages(QByteArray&,QHostAddress&,quint16)),Qt::DirectConnection);

    connect(m_pRadioCommunication,SIGNAL(SerialSendCMDRemoteCtrolOpenSignal(QByteArray&)),
            m_pSerialPortThread,SLOT(writeMessages(QByteArray&)),Qt::DirectConnection);
//    connect(m_pRadioCommunication,SIGNAL(SerialSendCMDRemoteCtrolOpenSignal(QByteArray&)),
//            this,SLOT(WriteSerialMessages(QByteArray&)),Qt::DirectConnection);

    connect(m_pRadioCommunication,SIGNAL(SendCMDRemoteCtrolCloseSignal(QByteArray&,QHostAddress&,quint16)),
                m_pUdpThread,SLOT(sendMessages(QByteArray&,QHostAddress&,quint16)),Qt::DirectConnection);
    connect(m_pRadioCommunication,SIGNAL(SendCMDInjectionSignal(QByteArray&,QHostAddress&,quint16)),
                m_pUdpThread,SLOT(sendMessages(QByteArray&,QHostAddress&,quint16)),Qt::DirectConnection);
    connect(m_pRadioCommunication,SIGNAL(SerialSendCMDInjectionSignal(QByteArray&)),
                m_pSerialPortThread,SLOT(writeMessages(QByteArray&)),Qt::DirectConnection);
//    connect(m_pRadioCommunication,SIGNAL(SerialSendCMDInjectionSignal(QByteArray&)),
//                this,SLOT(WriteSerialMessages(QByteArray&)),Qt::DirectConnection);


    connect(m_pRadioCommunication,SIGNAL(SendCMDChangeModeSignal(QByteArray&,QHostAddress&,quint16)),
                m_pUdpThread,SLOT(sendMessages(QByteArray&,QHostAddress&,quint16)),Qt::DirectConnection);
    connect(m_pRadioCommunication,SIGNAL(SendCMDChangeChannelSignal(QByteArray&,QHostAddress&,quint16)),
                m_pUdpThread,SLOT(sendMessages(QByteArray&,QHostAddress&,quint16)),Qt::DirectConnection);
    connect(m_pRadioCommunication,SIGNAL(SendCMDChangeTxSignal(QByteArray&,QHostAddress&,quint16)),
                m_pUdpThread,SLOT(sendMessages(QByteArray&,QHostAddress&,quint16)),Qt::DirectConnection);
    connect(m_pRadioCommunication,SIGNAL(SendCMDChangeRxSignal(QByteArray&,QHostAddress&,quint16)),
                m_pUdpThread,SLOT(sendMessages(QByteArray&,QHostAddress&,quint16)),Qt::DirectConnection);
    connect(m_pRadioCommunication,SIGNAL(SendCMDChangePowSignal(QByteArray&,QHostAddress&,quint16)),
                m_pUdpThread,SLOT(sendMessages(QByteArray&,QHostAddress&,quint16)),Qt::DirectConnection);
    connect(m_pRadioCommunication,SIGNAL(SendCMDChangeDSCEmitDataTypeSignal(QByteArray&,QHostAddress&,quint16)),
                m_pUdpThread,SLOT(sendMessages(QByteArray&,QHostAddress&,quint16)),Qt::DirectConnection);
    connect(m_pRadioCommunication,SIGNAL(SendCMDChangeATTSignal(QByteArray&,QHostAddress&,quint16)),
                m_pUdpThread,SLOT(sendMessages(QByteArray&,QHostAddress&,quint16)),Qt::DirectConnection);
    connect(m_pRadioCommunication,SIGNAL(SendCMDChangeAGCAndMGCSignal(QByteArray&,QHostAddress&,quint16)),
                m_pUdpThread,SLOT(sendMessages(QByteArray&,QHostAddress&,quint16)),Qt::DirectConnection);
    connect(m_pRadioCommunication,SIGNAL(SendCMDChangeSQLSignal(QByteArray&,QHostAddress&,quint16)),
                m_pUdpThread,SLOT(sendMessages(QByteArray&,QHostAddress&,quint16)),Qt::DirectConnection);
    connect(m_pRadioCommunication,SIGNAL(SendCMDChangeSilenceSignal(QByteArray&,QHostAddress&,quint16)),
                m_pUdpThread,SLOT(sendMessages(QByteArray&,QHostAddress&,quint16)),Qt::DirectConnection);
    connect(m_pRadioCommunication,SIGNAL(SendCMDQueryPOWTrimSignal(QByteArray&,QHostAddress&,quint16)),
                m_pUdpThread,SLOT(sendMessages(QByteArray&,QHostAddress&,quint16)),Qt::DirectConnection);
    connect(m_pRadioCommunication,SIGNAL(SendCMDChangeTuneModeSignal(QByteArray&,QHostAddress&,quint16)),
                m_pUdpThread,SLOT(sendMessages(QByteArray&,QHostAddress&,quint16)),Qt::DirectConnection);
    connect(m_pRadioCommunication,SIGNAL(SendCMDQuerySelfCheckSignal(QByteArray&,QHostAddress&,quint16)),
                m_pUdpThread,SLOT(sendMessages(QByteArray&,QHostAddress&,quint16)),Qt::DirectConnection);
    connect(m_pRadioCommunication,SIGNAL(SendCMDQueryHostInfoSignal(QByteArray&,QHostAddress&,quint16)),
                m_pUdpThread,SLOT(sendMessages(QByteArray&,QHostAddress&,quint16)),Qt::DirectConnection);
    connect(m_pRadioCommunication,SIGNAL(SendCMDQueryStatusSignal(QByteArray&,QHostAddress&,quint16)),
                m_pUdpThread,SLOT(sendMessages(QByteArray&,QHostAddress&,quint16)),Qt::DirectConnection);
    connect(m_pRadioCommunication,SIGNAL(SendCMDTuneDebugModeStateSignal(QByteArray&,QHostAddress&,quint16)),
                m_pUdpThread,SLOT(sendMessages(QByteArray&,QHostAddress&,quint16)),Qt::DirectConnection);
    connect(m_pRadioCommunication,SIGNAL(SendCMDSystemQuerySignal(QByteArray&,QHostAddress&,quint16)),
                m_pUdpThread,SLOT(sendMessages(QByteArray&,QHostAddress&,quint16)),Qt::DirectConnection);
    connect(m_pRadioCommunication,SIGNAL(SendCMDPTTSettingSignal(QByteArray&,QHostAddress&,quint16)),
                m_pUdpThread,SLOT(sendMessages(QByteArray&,QHostAddress&,quint16)),Qt::DirectConnection);
    connect(m_pRadioCommunication,SIGNAL(SerialSendCMDPTTSettingSignal(QByteArray&)),
                m_pSerialPortThread,SLOT(writeMessages(QByteArray&)),Qt::DirectConnection);


    connect(m_pRadioCommunication,SIGNAL(SendCMDChannelStateQuerySignal(QByteArray&,QHostAddress&,quint16)),
                m_pUdpThread,SLOT(sendMessages(QByteArray&,QHostAddress&,quint16)),Qt::DirectConnection);
    connect(m_pRadioCommunication,SIGNAL(SendMainStationStateSettingSignal(QByteArray&,QHostAddress&,quint16)),
                m_pUdpThread,SLOT(sendMessages(QByteArray&,QHostAddress&,quint16)),Qt::DirectConnection);
    connect(m_pRadioCommunication,SIGNAL(SendCMDChannelEmitQuerySignal(QByteArray&,QHostAddress&,quint16)),
                m_pUdpThread,SLOT(sendMessages(QByteArray&,QHostAddress&,quint16)),Qt::DirectConnection);
    //UDP---->Object
    connect(m_pUdpThread,SIGNAL(RadioCommunicationSignal(char *, int )),
                m_pRadioCommunication,SLOT(receiverRadioInfo(char *, int )),Qt::DirectConnection);
    connect(m_pSerialDataDealThread,SIGNAL(RadioCommunicationSignal(char *, int )),
                m_pRadioCommunication,SLOT(receiverRadioInfo(char *, int )),Qt::DirectConnection);
    connect(m_pUdpThread,SIGNAL(StransforLayerCommunication(char*,int)),
            m_StransforLayerCommunication,SLOT(receiveMessages(char*,int)),Qt::DirectConnection);
    connect(m_pUdpThread,SIGNAL(ReplyofQueryFreqSignal(char*,int)),this,SLOT(ReplyofQueryFreqSlot(char*,int)),Qt::DirectConnection);
    connect(&timer,SIGNAL(timeout()),this,SLOT(DealTimeOutSlot()),Qt::DirectConnection);
    connect(m_pRadioCommunication,SIGNAL(TuneSuccessSignal()),this,SLOT(UpdateTuneStateSlot()),Qt::DirectConnection);
    connect(m_physicallayer,SIGNAL(physicallSendOK()),this,SLOT(DealPHYStateSlot()),Qt::DirectConnection);
//serial ???????????????????????????????????????????????????????
    connect(this,SIGNAL(MainWorkFlowShiftAntennaToRadioSignal()),
            m_pShiftAntenna,SLOT(writeshiftToRadioMessages()),Qt::DirectConnection);

    connect(m_pShiftAntenna,SIGNAL(ShiftAntennaToRadioSignal(char*,int)),
            m_pSerialPortThread,SLOT(writeMessages(char*,int)),Qt::DirectConnection);

    connect(m_pShiftAntenna,SIGNAL(ShiftAntennaToRadioSignal(QByteArray &)),
            m_pSerialPortThread,SLOT(writeMessages(QByteArray &)),Qt::DirectConnection);

    connect(m_pShiftAntenna,SIGNAL(ShiftAntennaToWidebandReceiverSignal(char*,int)),m_pSerialPortThread,SLOT(writeMessages(char*,int)),Qt::DirectConnection);

    connect(m_pSerialPortThread,SIGNAL(getShifResultSignal(char*,int)),
            this,SLOT(getShifResultSlot(char*,int)),Qt::DirectConnection);
//serial ??????????????????????????????????????????????????????
    connect(this,SIGNAL(SendMessagesStateSignal(char*,int,int,int)),
            m_StransforLayerCommunication,SLOT(SendMessagesState(char*,int,int,int)),Qt::DirectConnection);
    connect(m_physicallayer,SIGNAL(getRadioMessages(unsigned char*,int)),
            m_StransforLayerCommunication,SLOT(haveMessagesToStransforSlot(unsigned char*,int)),Qt::DirectConnection);


    connect(this,SIGNAL(updateStranforLayRxValue(int)),m_StransforLayerCommunication,SLOT(updateRxValue(int)),Qt::DirectConnection);

    connect(m_pRadioCommunication,SIGNAL(SendGPSInfo(QString,QString,QString,QString)),
            m_StransforLayerCommunication,SLOT(haveGPSToStransforSlot(QString,QString,QString,QString)),Qt::DirectConnection);
    //connect(this,SIGNAL(sendMessage(char*, QHostAddress,quint16)),m_pUdpThread,SLOT(sendMessage(char*,QHostAddress,quint16)),Qt::DirectConnection);
//    connect(m_StransforLayerConmunication,SIGNAL(sendMessage(QByteArray&,QHostAddress&,quint16&)),
//            m_pUdpThread,SIGNAL(sendMessageSignal(QByteArray&,QHostAddress&,quint16&)),Qt::DirectConnection);

    //m_pRadioCommunication->SendCMDRemoteCtrolOpen();
    //m_pRadioCommunication->SendCMDInjectionSlot("SSB",299,1605000,1605000);
//    m_pRadioCommunication->SendCMDManualtuneSlot();
//    m_pRadioCommunication->SendMainStationStateSettingSlot("DSC","H",2,"MGC",3,false,20,false
//                                                           ,1);
    //"DSC", "H", 2,"MGC",3, false, 20,false, 1
//    m_pQueryFreq->needQueryFreq();
    //emit writeshiftToRadioMessagesSignal();
//    QString str = "I am chinese!";
//    QByteArray array;
//    array = str.toLatin1();
//    needSendMessagesToPhysical(array.data(),array.size());
    //emit writeshiftToRadioMessagesSignal();
//    QThread::sleep(1);
//    needSendMessagesToPhysical(array.data(),array.size());
    //emit writeshiftToWidebandReceiverSignal();
    //emit MainWorkFlowShiftAntennaToRadioSignal();
    m_pSerial = NULL;
    while (m_pSerial == NULL) {
        m_pSerial = m_pSerialPortThread->GetSerial();
    }

    int times = 0;
    emit needQueryFreqSignal();
    while(1)
    {
        if(isGetChannels)
        {
            qDebug()<<"Get channels OK";
            break;
        }
        else
        {
            //
            QThread::msleep(500);
            times++;
            if(times==10)
            {
                qDebug()<<"Get channels time out";
                return;
            }
        }
    }
    times = 1;
    isGetChannels = false;
    isTuneOK = false;
    m_pRadioCommunication->SendCMDRemoteCtrolOpen();
    m_pRadioCommunication->SendCMDInjectionSlot("SSB",278,rx[0]*1000,tx[0]*1000);
    qDebug()<<"tx:"<<tx[0]*1000<<"rx:"<<rx[0]*1000;
    //emit MainWorkFlowShiftAntennaToRadioSignal();

    while(1)
    {
        if(isTuneOK)
        {
            qDebug()<<" InJection OK----------------------------------";
            break;
        }
        else
        {
            //
            QThread::msleep(1000);
            times++;
            if(times == 15)//8sec
            {
                qDebug()<<" InJection time out";
                //m_pShiftAntenna->writeshiftToRadioMessages();
                return;
            }
        }
    }
    isTuneOK = false;
    m_pRadioCommunication->SendCMDRemoteCtrolOpen();
    m_pRadioCommunication->SendCMDPTTSettingSlot(PTT_RECEIVE);//emit
}

MainWorkFlow::~MainWorkFlow()
{
    m_pRadioCommunication->SendCMDRemoteCtrolClose();
    delete readConfig;
    delete m_StransforLayerCommunication;
    delete m_pRadioCommunication;
}

void MainWorkFlow::init()
{

}

void MainWorkFlow::setShiftAntenna(ShiftAntenna *t)
{
    m_pShiftAntenna = t;
}

void MainWorkFlow::sendMessageSlot(QByteArray&data, QHostAddress& address,quint16 port)
{
    emit sendMessage(data, address,port);
    //qDebug()<<"Test"<<data;
}

void MainWorkFlow::needSendMessagesToPhysical(char *buff, int len,char *messagebuff,int messagelenth)
{
    //
    static char tmpbuff[4096];
    memcpy(tmpbuff,buff,len);
    static int sendTimes = 0;
    qDebug()<<__FILE__<<__FUNCTION__<<isGetChannels<<"sendTimes:"<< ++sendTimes;
    //emit writeshiftToRadioMessagesSignal();
    isGetChannels = false;
    emit needQueryFreqSignal();
    int times = 0;
    while(1)
    {
        if(isGetChannels)
        {
            qDebug()<<"Get channels OK";
            break;
        }
        else
        {
            //
            QThread::msleep(500);
            times++;
            if(times==10)
            {
                qDebug()<<"Get channels time out";
                emit SendMessagesStateSignal(tmpbuff,len,0,0);
                return;
            }
        }
    }
    times = 1;
    isGetChannels = false;
    qDebug()<<"Test1"<<"m_ChannelsCount"<<m_ChannelsCount<<"rx[0]"<<rx[0]<<QThread::currentThread();
    //emit writeshiftToRadioMessagesSignal();

    //qDebug()<<"Shift Radio OK";
//    while(1)
//    {
//        if(isShiftRadioOk)
//        {
//            qDebug()<<"Shift Radio OK";
//            break;
//        }
//        else
//        {
//            //
//            QThread::msleep(1000);
//            times++;
//            if(times==20)
//            {
//                qDebug()<<"Shift Radio time out";
//                return;
//            }
//        }
//    }
    //m_pShiftAntenna->writeshiftToWidebandReceiver();
TRY_AGAIN:
    //m_ChannelsCount = 1;
    for(int i = 0; i < m_ChannelsCount; i++)
    {
        isTuneOK = false;
        m_pRadioCommunication->SendCMDRemoteCtrolOpen();
        m_pRadioCommunication->SendCMDInjectionSlot("SSB",299,rx[i]*1000,tx[i]*1000);
        times = 1;
        while(1)
        {
            if(isTuneOK)
            {
                qDebug()<<" InJection OK----------------------------------";
                break;
            }
            else
            {
                //
                QThread::msleep(1000);
                times++;
                if(times == 15)//15sec
                {
                    qDebug()<<" InJection time out";
                    if(i == m_ChannelsCount-1)
                    {
                        emit SendMessagesStateSignal(tmpbuff,len,0,tx[i]);
                        return;
                    }
                    else
                    {
                        goto TRY_AGAIN;
                    }
                }
            }
        }
        m_pRadioCommunication->SendCMDRemoteCtrolOpen();
        m_pRadioCommunication->SendCMDPTTSettingSlot(PTT_SEND);//emit
        m_physicallayer->encodeSlot(messagebuff,messagelenth);
        while(!isSendOK)
        {

        }
        emit SendMessagesStateSignal(tmpbuff,len,1,tx[i]);
        isSendOK = false;
        qDebug()<<"Send finised"<<isSendOK;
    }
    m_pRadioCommunication->SendCMDRemoteCtrolOpen();
    m_pRadioCommunication->SendCMDInjectionSlot("SSB",299,rx[0]*1000,tx[0]*1000);
    m_pRadioCommunication->SendCMDPTTSettingSlot(PTT_RECEIVE);//emit
    //emit writeshiftToWidebandReceiverSignal();
}
//void MainWorkFlow::needSendMessagesToPhysical(char *buff, int len,char *messagebuff,int messagelenth)
//{
//    m_pBuff = buff;
//    m_len = len;
//    m_pMessagebuff = messagebuff;
//    m_Messagelenth = messagelenth;
//    isSendGetChannels = true;
//    isNeedSendMessages = true;
//    emit needQueryFreqSignal();
//    timer.setSingleShot(true);
//    timer.start(1000);
//}
void MainWorkFlow::ReplyofQueryFreqSlot(char *buff, int len)
{
    qDebug()<<__FUNCTION__<<"Len:"<<len;
    memcpy(&m_Freqdata, (QueryFreqData*)buff,len);
    if((rx[0] != m_Freqdata.rx1) || (tx[0] != m_Freqdata.tx1)||
            (rx[1] != m_Freqdata.rx2) || (tx[1] != m_Freqdata.tx2)||
            (rx[2] != m_Freqdata.rx3) || (tx[2] != m_Freqdata.tx3))
    {
    //qDebug()<<m_Freqdata.time<<m_Freqdata.tx1;
        rx[0] = m_Freqdata.rx1;
        tx[0] = m_Freqdata.tx1;
        rx[1] = m_Freqdata.rx2;
        tx[1] = m_Freqdata.tx2;
        rx[2] = m_Freqdata.rx3;
        tx[2] = m_Freqdata.tx3;
        m_pRadioCommunication->SendCMDRemoteCtrolOpen();
        m_pRadioCommunication->SendCMDInjectionSlot("SSB",299,rx[0]*1000,tx[0]*1000);
        emit updateStranforLayRxValue(rx[0]);
    }
    if(!isGetChannels)
    {
        timer.stop();
        isSendGetChannels = false;
        m_ChannelsCount = 0;
        qDebug()<<rx[0]<<tx[0];
        if(m_Freqdata.tx1 != 0)
        {
            for(int i = 0; i < 3; i++)
            {
                if(rx[i] != 0 && tx[i] != 0)
                {
                    m_ChannelsCount++;
                }
                else
                {
                    break;
                }
            }
            isGetChannels = true;
        }
    }
}

void MainWorkFlow::UpdateTuneStateSlot()
{
    isTuneOK = true;
    qDebug()<<"isTuneOK"<<isTuneOK;
}

void MainWorkFlow::DealTimeOutSlot()
{
    isTimeout = true;
    if(isSendGetChannels)
    {
        qDebug()<<"Get Channel time Out";
    }
    if(isSendShiftAntenna)
    {
        qDebug()<<"Shift Antenna time Out";
    }
    qDebug()<<"time Out";

}

void MainWorkFlow::DealPHYStateSlot()
{
    isSendOK = true;
}

void MainWorkFlow::DealShiftRadioResult()
{
    isShiftRadioOk = true;
    qDebug()<<"isShiftRadioOk"<<isShiftRadioOk;
}

void MainWorkFlow::DealShiftWidebandReceiverResult()
{

}

void MainWorkFlow::getShifResultSlot(char *buff, int len)
{
    if(isNeedSendMessages)
    {
        if(len > 0)
        {
            timer.stop();
            if(buff[len-1] == 0x55)
            {
                isSendShiftAntenna = false;
                for(int i = 0; i< m_ChannelsCount; i++)
                {
                    m_pRadioCommunication->SendCMDRemoteCtrolOpen();
                    m_pRadioCommunication->SendCMDInjectionSlot("SSB",299,rx[i]*1000,tx[i]*1000);

                }
            }
        }
    }
}

void MainWorkFlow::WriteSerialMessages(QByteArray &array)
{
    qDebug()<<__FUNCTION__<<"Start Serial";
    int c = m_pSerial->write(array);
    qDebug()<<__FUNCTION__<<"Len"<<c;
}
