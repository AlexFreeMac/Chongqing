#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QThread>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
class SerialPort : public QThread
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = 0);
    QSerialPort* GetSerial();
protected:
    void run();
signals:
    void shiftRadioSuccess();
    void shiftWidebandReceiver();
    void getShifResultSignal(char *,int );
public slots:
    void readMessages();
    void writeMessages(char *buff, int len);
    void writeMessages(QByteArray &array);
private:
    QSerialPortInfo *pSerialInfo;
    QSerialPort *m_pSerial;
};

#endif // SERIALPORT_H
