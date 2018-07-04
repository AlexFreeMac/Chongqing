#include "serialradiodatadeal.h"
#include "globalVariable.h"
#include <QDebug>
SerialRadioDataDeal::SerialRadioDataDeal()
{
}

void SerialRadioDataDeal::getDate(char *tmp, int count)
{
    for(int i = 0; i < count; i++)
    {
        g_usedBytes.acquire();
        tmp[i] = g_BUFF[g_ReadIndex++];
        if(g_ReadIndex == 1024)
        {
            g_ReadIndex = 0;
        }
        g_freeBytes.release();
    }
}

void SerialRadioDataDeal::run()
{
    char radioBuff[512];
    char tmpbuffHeader[2];
    char tmpbuffLen[2];
    char tmpdata[256];
    int datalen = 0;
    while(1)
    {
        memset(radioBuff,0,512);
        memset(tmpdata,0,512);
        tmpbuffHeader[0] = 0x00;
        tmpbuffHeader[1] = 0x00;
        tmpbuffLen[0] = 0x00;
        tmpbuffLen[1] = 0x00;
        getDate(tmpbuffHeader,2);
        if((tmpbuffHeader[0] == 0x7E) && (tmpbuffHeader[1] == 0x7E))
        {
            getDate(tmpbuffLen,2);
            datalen = tmpbuffLen[0]*16+tmpbuffLen[1];
            qDebug()<<"Data len:"<<datalen;
            radioBuff[0] = tmpbuffHeader[0];
            radioBuff[1] = tmpbuffHeader[1];
            radioBuff[2] = tmpbuffLen[0];
            radioBuff[3] = tmpbuffLen[1];
            getDate(tmpdata,datalen);
            for(int i = 0; i < datalen; i++)
            {
                radioBuff[4+i] = tmpdata[i];
            }
            emit RadioCommunicationSignal(radioBuff,datalen+4);
        }
    }
}
