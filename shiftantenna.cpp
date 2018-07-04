#include "shiftantenna.h"
#include "QDebug"
#include "stdio.h"
ShiftAntenna::ShiftAntenna()
{
}
void ShiftAntenna::writeshiftToRadioMessages()
{
    char shiftToRadio = 0xee;
    //qDebug()<<__FUNCTION__<<m_pSerial->write(&shiftToRadio,1)<<QThread::currentThread();
    QByteArray array;
    array.append(shiftToRadio);
    qDebug()<<__FUNCTION__<<"Array count"<<array.count();
    //emit ShiftAntennaToRadioSignal(&shiftToRadio, 1);
    emit ShiftAntennaToRadioSignal(array);

}

void ShiftAntenna::writeshiftToWidebandReceiver()
{
    char shiftToWidebandReceiver = 0x5e;
    //qDebug()<<__FUNCTION__<<m_pSerial->write(&shiftToWidebandReceiver,1);
    emit ShiftAntennaToWidebandReceiverSignal(&shiftToWidebandReceiver, 1);
}

