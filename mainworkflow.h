#ifndef MAINWORKFLOW_H
#define MAINWORKFLOW_H

#include <QObject>
#include <readconfigfile.h>
#include <QThread>
#include <stransforlayercommunication.h>
#include <radiocommunication.h>
#include <udpsocket.h>
#include <physicallayercommunication.h>
#include <queryfrequency.h>
#include <shiftantenna.h>
#include <serialport.h>
#include <serialradiodatadeal.h>
#include <messagelistcontrol.h>
#define PTT_SEND 0x01
#define PTT_RECEIVE 0x00
class MainWorkFlow : public QObject
{
    Q_OBJECT
public:
    explicit MainWorkFlow(QObject *parent = 0);
    ~MainWorkFlow();
    void init();
    void setShiftAntenna(ShiftAntenna* t);
signals:
    void sendMessage(QByteArray, QHostAddress&,quint16&);
    void needQueryFreqSignal();
    void SendMessagesStateSignal(char* str, int len,int state, int tx);
    //void writeshiftToRadioMessagesSignal();
    void MainWorkFlowShiftAntennaToRadioSignal();
    void MainWorkFlowShiftAntennaToWidebandReceiverSignal();
    void updateStranforLayRxValue(int );
public slots:
    void sendMessageSlot(QByteArray&data, QHostAddress& address,quint16 port);
    void needSendMessagesToPhysical(char *buff,int len, char *messagebuff,int messagelenth);
    void ReplyofQueryFreqSlot(char *buff,int len);
    void UpdateTuneStateSlot();
    void DealTimeOutSlot();
    void DealPHYStateSlot();
    void DealShiftRadioResult();
    void DealShiftWidebandReceiverResult();
    void getShifResultSlot(char*buff,int len);
    void WriteSerialMessages(QByteArray &array);
private:
        ReadConfigFile *readConfig;
        MessageListControl *m_MessageListControl;
        StransforLayerCommunication *m_StransforLayerCommunication;
        RadioCommunication *m_pRadioCommunication;
        PhysicalLayerCommunication *m_physicallayer;
        QueryFrequency *m_pQueryFreq;
        ShiftAntenna *m_pShiftAntenna;

        SerialRadioDataDeal * m_pSerialDataDealThread;

        UdpSocket *m_pUdpThread;
        SerialPort* m_pSerialPortThread;
        QSerialPort* m_pSerial;

        QThread m_RadioCommunicationThread;
        QThread m_StransforLayerCommunicationThread;
        QThread m_physicallayerThread;
        QThread m_ShiftAntennaThread;

        bool isGetChannels;
        bool isSendGetChannels;
        bool isTimeout;
        bool isTuneOK;
        bool isSendOK;
        bool isShiftRadioOk;
        bool isSendShiftAntenna;
        bool isNeedSendMessages;
        QTimer timer;
        QueryFreqData m_Freqdata;
        int rx[3];
        int tx[3];
        int m_ChannelsCount;

        char *m_pBuff;
        int m_len;
        char *m_pMessagebuff;
        int m_Messagelenth;

};

#endif // MAINWORKFLOW_H
