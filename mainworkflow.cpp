#include "mainworkflow.h"
#include "qmetatype.h"
MainWorkFlow::MainWorkFlow(QObject *parent) :
    QObject(parent)
{
    readConfig = new ReadConfigFile();

    m_pUdpThread = new UDPThread();
    m_pUdpThread->moveToThread(&m_UDPThread);
    m_UDPThread.start();

    m_StransforLayerConmunication = new StransforLayerConmunication();
    m_StransforLayerConmunication->moveToThread(&m_StransforLayerConmunicationThread);
    m_StransforLayerConmunicationThread.start();

    m_pRadioConmunication = new RadioConmunication();
    m_pRadioConmunication->moveToThread(&m_RadioConmunicationThread);
    m_RadioConmunicationThread.start();
    //qRegisterMetaType<QHostAddress>("QHostAddress");
    //connect(m_StransforLayerConmunication,SIGNAL(sendMessage(QByteArray&, QHostAddress&,quint16&)),this,SLOT(sendMessageSlot(QByteArray&, QHostAddress&,quint16&)),Qt::DirectConnection);
    //connect(this,SIGNAL(sendMessage(char*, QHostAddress,quint16)),m_pUdpThread,SLOT(sendMessage(char*,QHostAddress,quint16)),Qt::DirectConnection);
    connect(m_StransforLayerConmunication,SIGNAL(sendMessage(QByteArray&,QHostAddress&,quint16&)),
            m_pUdpThread,SIGNAL(sendMessageSignal(QByteArray&,QHostAddress&,quint16&)),Qt::DirectConnection);

}

MainWorkFlow::~MainWorkFlow()
{
    delete readConfig;
    delete m_StransforLayerConmunication;
}

void MainWorkFlow::sendMessageSlot(QByteArray&data, QHostAddress& address,quint16& port)
{
    emit sendMessage(data, address,port);
    qDebug()<<"Test"<<data;
}
