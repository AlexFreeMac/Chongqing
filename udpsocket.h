#ifndef UDPSOCKET_H
#define UDPSOCKET_H
#include <QObject>
#include <QUdpSocket>
#include <QThread>

typedef struct QueryFreqData
{
    int tx1;
    int rx1;
    int tx2;
    int rx2;
    int tx3;
    int rx3;
    int time;
}QueryFreqData;

class UdpSocket:public QThread
{
    Q_OBJECT
public:
    UdpSocket();
protected:
    void run();
public slots:
    void readMessages();
    void sendMessages(QByteArray &byteArray, QHostAddress &address,quint16 port);
signals:
    void RadioCommunicationSignal(char *, int );
    void StransforLayerCommunication(char *, int );
    void ReplyofQueryFreqSignal(char *, int );

private:
    QUdpSocket *m_psocket;
};

#endif // UDPSOCKET_H
