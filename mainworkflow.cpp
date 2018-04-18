#include "mainworkflow.h"

MainWorkFlow::MainWorkFlow(QObject *parent) :
    QObject(parent)
{
    readConfig = new ReadConfigFile();
    m_StransforLayerConmunication = new StransforLayerConmunication();
    m_StransforLayerConmunication->moveToThread(&m_StransforLayerConmunicationThread);
    m_StransforLayerConmunicationThread.start();

}

MainWorkFlow::~MainWorkFlow()
{
    delete readConfig;
    delete m_StransforLayerConmunication;
}
