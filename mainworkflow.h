#ifndef MAINWORKFLOW_H
#define MAINWORKFLOW_H

#include <QObject>
#include <readconfigfile.h>
#include <QThread>
#include <stransforlayerconmunication.h>
class MainWorkFlow : public QObject
{
    Q_OBJECT
public:
    explicit MainWorkFlow(QObject *parent = 0);
    ~MainWorkFlow();
signals:

public slots:

private:
        ReadConfigFile *readConfig;
        StransforLayerConmunication *m_StransforLayerConmunication;
        QThread m_RadioConmunicationThread;
        QThread m_StransforLayerConmunicationThread;
};

#endif // MAINWORKFLOW_H
