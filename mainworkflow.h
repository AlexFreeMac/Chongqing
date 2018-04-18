#ifndef MAINWORKFLOW_H
#define MAINWORKFLOW_H

#include <QObject>
#include <readconfigfile.h>
#include <QThread>
#include <stransforlayerconmunication.h>
#include <radioconmunication.h>
#include <udpthread.h>
class MainWorkFlow : public QObject
{
    Q_OBJECT
public:
    explicit MainWorkFlow(QObject *parent = 0);
    ~MainWorkFlow();
signals:
    void sendMessage(QByteArray, QHostAddress&,quint16&);
public slots:
    void sendMessageSlot(QByteArray&data, QHostAddress& address,quint16& port);
private:
        ReadConfigFile *readConfig;
        StransforLayerConmunication *m_StransforLayerConmunication;
        RadioConmunication *m_pRadioConmunication;
        UDPThread *m_pUdpThread;
        QThread m_RadioConmunicationThread;
        QThread m_StransforLayerConmunicationThread;
        QThread m_UDPThread;
};

#endif // MAINWORKFLOW_H
