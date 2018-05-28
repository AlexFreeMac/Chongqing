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
    qDebug()<<__FUNCTION__<<QThread::currentThread();
    emit ShiftAntennaToRadioSignal(&shiftToRadio, 1);

}

void ShiftAntenna::writeshiftToWidebandReceiver()
{
    char shiftToWidebandReceiver = 0x5e;
    //qDebug()<<__FUNCTION__<<m_pSerial->write(&shiftToWidebandReceiver,1);
    emit ShiftAntennaToWidebandReceiverSignal(&shiftToWidebandReceiver, 1);
}

