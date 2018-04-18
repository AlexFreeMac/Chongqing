#ifndef STRANSFORLAYERCONMUNICATION_H
#define STRANSFORLAYERCONMUNICATION_H

#include <QObject>
#include <QTimer>
#include <QHostAddress>
#include <QByteArray>
class StransforLayerConmunication : public QObject
{
    Q_OBJECT
public:
    explicit StransforLayerConmunication(QObject *parent = 0);

signals:
    void sendMessage(QByteArray &data, QHostAddress &host,quint16 &port);
public slots:
    void sendMessages();
private:
    QTimer m_SendTimer;
};

#endif // STRANSFORLAYERCONMUNICATION_H
