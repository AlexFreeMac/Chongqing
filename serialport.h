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
protected:
    void run();
signals:
    void shiftRadioSuccess();
    void shiftWidebandReceiver();
    void getShifResultSignal(char *,int );
public slots:
    void readMessages();
    void writeMessages(char *buff, int len);
private:
    QSerialPort *m_pSerial;
};

#endif // SERIALPORT_H
