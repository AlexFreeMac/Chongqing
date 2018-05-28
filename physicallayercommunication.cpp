#include "physicallayercommunication.h"
#include "QDebug"
#include "stdio.h"
unsigned char g_Buff[4096];
int g_bufferlen = 0;
bool isHaveDate;
PhysicalLayerCommunication::PhysicalLayerCommunication(QObject *parent) :
    QObject(parent)
{
    isHaveDate = false;

    player = NULL;
    player = init_player();
    recorder = NULL;
    recorder = init_recorder(OnOliviaDecoded);
    start_record(recorder);
    connect(&timer,SIGNAL(timeout()),this,SLOT(timeOutSlot()));
    timer.start(200);//200ms
    qDebug()<<"is_running record status:"<<is_running(recorder);
}

PhysicalLayerCommunication::~PhysicalLayerCommunication()
{
    free_olivia(player);
    free_olivia(recorder);
}

void PhysicalLayerCommunication::OnOliviaDecoded(unsigned char * buffer, int bufferlen)
{
    qDebug()<<__FUNCTION__<<"CurrentThread"<<QThread::currentThread()<<"bufferLen:"<<bufferlen;
    memcpy(g_Buff,buffer,bufferlen);
    g_bufferlen = bufferlen;
    for(int i = 0; i < bufferlen; i++)
    {
        printf("0X%02X ",buffer[i]);
    }
    printf("\n");
    //
    isHaveDate = true;

}

void PhysicalLayerCommunication::encodeSlot(char *str, int len)
{
    //short buffer[2048];
    //encode(encoder, (unsigned char*)str, len);
    //int lenth = process(encoder, buffer, 2048);
//    char tmp[5];
//    tmp[0] = 0x7E;
//    tmp[1] = 0x61;
//    tmp[2] = 0x61;
//    tmp[3] = 0x61;
//    tmp[4] = 0x29;
    qDebug()<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
    for(int i = 0; i< len;i++)
    {
        printf("0X%02X ",(unsigned char*)str[i]);
    }
    printf("\n");
    qDebug()<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
    stop_olivia(recorder);
    if (play(player, (unsigned char*)str, len))
    {
        while (is_running(player))
        {
            QThread::usleep(100);
        }
    }
    else
    {
        qDebug()<<"Play error";
        start_record(recorder);
        emit physicallSendFail();
        return;
    }
    start_record(recorder);
    qDebug()<<"is_running record status:"<<is_running(recorder);
    //emit writeshiftToWidebandReceiverSignal();
    emit physicallSendOK();

}

void PhysicalLayerCommunication::timeOutSlot()
{
    if(isHaveDate)
    {
        emit getRadioMessages(g_Buff,g_bufferlen);
        isHaveDate = false;
    }
}


