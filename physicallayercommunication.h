#ifndef PHYSICALLAYERCOMMUNICATION_H
#define PHYSICALLAYERCOMMUNICATION_H

#include <QObject>
#include <QThread>
#include <physical.h>
#include <QTimer>
class PhysicalLayerCommunication : public QObject
{
    Q_OBJECT
public:
    explicit PhysicalLayerCommunication(QObject *parent = 0);
    ~PhysicalLayerCommunication();
    void  static OnOliviaDecoded(unsigned char * buffer, int bufferlen);
private:
    void * player;
    void * recorder;
signals:
    void DecodeSignal(unsigned char *, int);
    void SendCodeAudio();
    void SendMessageStatus(char* , int ,int ,int);
    void physicallSendOK();
    void physicallSendFail();
    void writeshiftToWidebandReceiverSignal();
    void getRadioMessages(unsigned char *, int );
public slots:
    void encodeSlot(char * str, int len);
    void timeOutSlot();
private:
    QTimer timer;

};

#endif // PHYSICALLAYERCOMMUNICATION_H
