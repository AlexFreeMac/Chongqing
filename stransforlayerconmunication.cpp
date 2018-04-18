#include "stransforlayerconmunication.h"
#include "globalVariable.h"
#include "QDebug"
StransforLayerConmunication::StransforLayerConmunication(QObject *parent) :
    QObject(parent)
{
    connect(&m_SendTimer,SIGNAL(timeout()),this,SLOT(sendMessages()));
    m_SendTimer.start(2000);
}



void StransforLayerConmunication::sendMessages()
{
    QString test="qiuhong,qiuhong";
    QByteArray cstr = test.toLatin1();
    //char *data;
    //data = test.toLatin1().data();

    QHostAddress address;
    address.setAddress(g_strTransforIP);
    emit sendMessage(cstr,address,g_TransportUdpPort);
}
