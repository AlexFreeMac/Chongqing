#ifndef RADIOCOMMUNICATION_H
#define RADIOCOMMUNICATION_H

#include <QObject>
#include <QByteArray>
#include <QHostAddress>
#include <QTimer>
#define ERROR_CMD_CODE 0x00
#define REMOTE_CONTROL_CMD_CODE 0x6C
#define MANUAL_TUNE_CMD_CODE 0x01
#define TUNE_REPORT_CMD_CODE 0x05
#define INJECTION_CMD_CODE 0x02
#define MODE_CMD_CODE 0x03
#define CHANNEL_CMD_CODE 0x04
#define EMIT_TX_FREQ_CMD_CODE 0x0B
#define EMIT_RX_FREQ_CMD_CODE 0x0C
#define EMIT_POW_CMD_CODE 0x0E
#define DSC_EMIT_DATA_TYPE_CMD_CODE 0x0F
#define ATT_CMD_CODE 0x10
#define AGC_OR_MGC_CMD_CODE 0x11
#define SQL_CMD_CODE 0x12
#define SILENCE_CMD_CODE 0x18
#define POWTRIM_SETTING_CMD_CODE 0x19
#define POWTRIM_QUERY_CMD_CODE 0x1a
#define TUNE_MODE_CMD_CODE 0x1c
#define SELFCHECK_CMD_CODE 0x66
#define HOST_INFO_QUERY_CMD_CODE 0x67
#define STATUS_QUERY_CMD_CODE 0x6A
#define TUNE_DEBUG_MODE_CMD_CODE 0x6b
#define SYSTEM_QUERY_CMD_CODE 0x6e
#define PTT_STATE_CMD_CODE 0x6f
#define CHANNEL_STATE_QUERY 0x73
#define MAIN_STATION_STATE_CMD_CODE 0x74
#define CHANNEL_EMIT_QUERY_CMD_CODE 0x75

class RadioCommunication : public QObject
{
    Q_OBJECT
public:
    explicit RadioCommunication(QObject *parent = 0);
signals:
    void SendCMDManualtuneSignal(QByteArray&, QHostAddress&, quint16);
    void SendCMDRemoteCtrolOpenSignal();
    void SendCMDRemoteCtrolOpenSignal(QByteArray&, QHostAddress&, quint16);
    void SerialSendCMDRemoteCtrolOpenSignal(QByteArray&);
    void SendCMDRemoteCtrolCloseSignal();
    void SendCMDRemoteCtrolCloseSignal(QByteArray&, QHostAddress&, quint16);
    void SendCMDInjectionSignal(QString , short , int , int );
    void SendCMDInjectionSignal(QByteArray&, QHostAddress&, quint16);
    void SerialSendCMDInjectionSignal(QByteArray&);

    void SendCMDChangeModeSignal(QString );
    void SendCMDChangeModeSignal(QByteArray&, QHostAddress&, quint16);
    void SendCMDChangeChannelSignal(QByteArray&, QHostAddress&, quint16);
    void SendCMDChangeChannelSignal(int);
    void SendCMDChangeTxSignal(int );
    void SendCMDChangeTxSignal(QByteArray&, QHostAddress&, quint16 );
    void SendCMDChangeRxSignal(int );
    void SendCMDChangeRxSignal(QByteArray&, QHostAddress&, quint16 );
    void SendCMDChangePowSignal(QString );
    void SendCMDChangePowSignal(QByteArray&, QHostAddress&, quint16);
    void SendCMDChangeDSCEmitDataTypeSignal(int);
    void SendCMDChangeDSCEmitDataTypeSignal(QByteArray&, QHostAddress&, quint16);
    void SendCMDChangeATTSignal(int value);
    void SendCMDChangeATTSignal(QByteArray&, QHostAddress&, quint16);
    void SendCMDChangeAGCAndMGCSignal(QString ,int );
    void SendCMDChangeAGCAndMGCSignal(QByteArray&, QHostAddress&, quint16);
    void SendCMDChangeSQLSignal(bool ,int);
    void SendCMDChangeSQLSignal(QByteArray&, QHostAddress&, quint16);
    void SendCMDChangeSilenceSignal(bool isopen);
    void SendCMDChangeSilenceSignal(QByteArray&, QHostAddress&, quint16);
    void SendCMDQueryPOWTrimSignal(QString );
    void SendCMDQueryPOWTrimSignal(QByteArray&, QHostAddress&, quint16);
    void SendCMDChangeTuneModeSignal(bool);
    void SendCMDChangeTuneModeSignal(QByteArray&, QHostAddress&, quint16);
    void SendCMDQuerySelfCheckSignal();
    void SendCMDQuerySelfCheckSignal(QByteArray&, QHostAddress&, quint16);
    void SendCMDQueryHostInfoSignal();
    void SendCMDQueryHostInfoSignal(QByteArray&, QHostAddress&, quint16);
    void SendCMDQueryStatusSignal();
    void SendCMDQueryStatusSignal(QByteArray&, QHostAddress&, quint16);
    void SendCMDTuneDebugModeStateSignal(bool isOpen);
    void SendCMDTuneDebugModeStateSignal(QByteArray&, QHostAddress&, quint16);
    void SendCMDSystemQuerySignal();
    void SendCMDSystemQuerySignal(QByteArray&, QHostAddress&, quint16);
    void SendCMDPTTSettingSignal(int );
    void SendCMDPTTSettingSignal(QByteArray&, QHostAddress&, quint16);
    void SerialSendCMDPTTSettingSignal(QByteArray&);

    void SendCMDChannelStateQuerySignal();
    void SendCMDChannelStateQuerySignal(QByteArray&, QHostAddress&, quint16);
    void SendMainStationStateSettingSignal(QString , QString , int /*RaidoRF-ATT*/,
                                         QString ,/**/int , bool , int ,
                                         bool , int );
    void SendMainStationStateSettingSignal(QByteArray&, QHostAddress&, quint16);
    void SendCMDChannelEmitQuerySignal();
    void SendCMDChannelEmitQuerySignal(QByteArray&, QHostAddress&, quint16);
    void TuneSuccessSignal();
    void TuneFailSignal();
    void SendGPSInfo(QString , QString , QString , QString );//QString co, QString lo, QString la, QString utcTime
public slots:
    void SendCMDManualtuneSlot();
    void SendCMDRemoteCtrolOpen();
    void SendCMDRemoteCtrolClose();
    void SendCMDInjectionSlot(QString mode, short channel, int rx, int tx);//zhupin
    void SendCMDChangeModeSlot(QString mode);
    void SendCMDChangeChannelSlot(int channel);
    void SendCMDChangeTxSlot(int tx);
    void SendCMDChangeRxSlot(int rx);
    void SendCMDChangePowSlot(QString value);
    void SendCMDChangeDSCEmitDataTypeSlot(int value);
    void SendCMDChangeATTSlot(int value);
    void SendCMDChangeAGCAndMGCSlot(QString mode,int value);
    void SendCMDChangeSQLSlot(bool isopen,int value);
    void SendCMDChangeSilenceSlot(bool isopen);
    void SendCMDQueryPOWTrimSlot(QString mode);
    void SendCMDChangeTuneModeSlot(bool isManual);
    void SendCMDQuerySelfCheckSlot();
    void SendCMDQueryHostInfoSlot();
    void SendCMDQueryStatusSlot();
    void SendCMDTuneDebugModeStateSlot(bool isOpen);
    void SendCMDSystemQuerySlot();
    void SendCMDPTTSettingSlot(int state);
    void SendCMDChannelStateQuerySlot();
    void SendMainStationStateSettingSlot(QString mode, QString sendRFvalue, int value/*RaidoRF-ATT*/,
                                         QString AGCOrMGCmode,/**/int AGCOrMGCvalue, bool isSQLOpen, int SQLvalue,
                                         bool tuneModeIsManual, int AntennaType);
    void SendCMDChannelEmitQuerySlot();
    void timeoutSlot();
    void receiverRadioInfo(char *buff, int len);
private:
    QTimer timer;
};

#endif // RADIOCOMMUNICATION_H
