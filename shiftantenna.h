#ifndef SHIFTANTENNA_H
#define SHIFTANTENNA_H

#include <QObject>
#include <QThread>

class ShiftAntenna :public QThread//: public QThread
{
    Q_OBJECT
public:
    ShiftAntenna();
signals:
    void ShiftAntennaToRadioSignal(char *, int);
    void ShiftAntennaToWidebandReceiverSignal(char *,int);
public slots:
    void writeshiftToRadioMessages();
    void writeshiftToWidebandReceiver();
public :
private:
    bool ischeckShiftToRadio;
    bool ischeckShitfToWideband;
};

#endif // SHIFTANTENNA_H
