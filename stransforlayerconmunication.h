#ifndef STRANSFORLAYERCONMUNICATION_H
#define STRANSFORLAYERCONMUNICATION_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
class StransforLayerConmunication : public QObject
{
    Q_OBJECT
public:
    explicit StransforLayerConmunication(QObject *parent = 0);

signals:

public slots:
    void readMessages();
    void sendMessages();
private:
    QUdpSocket *m_pStransforLayerSocket;
    QTimer m_SendTimer;
};

#endif // STRANSFORLAYERCONMUNICATION_H
