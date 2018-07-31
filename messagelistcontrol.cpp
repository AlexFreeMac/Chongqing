#include "messagelistcontrol.h"
#include <QDebug>
#include <globalVariable.h>
MessageListControl::MessageListControl()
{
    m_preMessagePtr = NULL;
}

void MessageListControl::run()
{
    exec();
}

void MessageListControl::addMessagesToQueue(char *buff, int len)
{
    char *buffPtr = new char[len];
    memcpy(buffPtr,buff,len);
    qDebug()<<".................."<<__FUNCTION__<<"Queue size"<<m_MesageQueue.size()<<"buff len:"<<len;
    if(m_MesageQueue.size() == 0)
    {
        m_MesageQueue.enqueue(buffPtr);
        m_MssageCountQueue.enqueue(len);
        if(g_isSendFinished)
        {
            nextMessages();
        }
    }
    else
    {
        m_MesageQueue.enqueue(buffPtr);
        m_MssageCountQueue.enqueue(len);
    }

}

void MessageListControl::nextMessages()
{
    qDebug()<<".................."<<__FUNCTION__<<m_preMessagePtr;
    g_isSendFinished = false;
    if(m_preMessagePtr != NULL)
    {
        delete[]m_preMessagePtr;
        m_preMessagePtr = NULL;
    }
    if(m_MesageQueue.size() != 0)
    {
        char* buffPtr = m_MesageQueue.dequeue();
        int len = m_MssageCountQueue.dequeue();
        m_preMessagePtr = buffPtr;
        emit NeedSendMessagesToPhyLayer(buffPtr,len);
    }
    else
    {
         g_isSendFinished = true;
    }
}
