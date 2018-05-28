#ifndef STRANSFORLAYERCOMMUNICATION_H
#define STRANSFORLAYERCOMMUNICATION_H

#include <QObject>
#include <QTimer>
#include <QHostAddress>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
//
#define JSON_TYPE_SEND_MESSAGES 10
#define JSON_TYPE_MESSAGES_SEND_SUCCESS 11
#define JSON_TYPE_MESSAGES_SEND_FAIL 12
#define JSON_TYPE_MESSAGES_RECEIVE 13
#define JSON_TYPE_SEND_LOCAL_REQUEST 20
#define JSON_TYPE_SEND_LOCAL_REQUEST_SUCCESS 21
#define JSON_TYPE_SEND_LOCAL_REQUEST_FAIL 22
#define JSON_TYPE_RECEIVE_LOCAL 23
#define JSON_TYPE_SEND_GPS_LOCAL 30
#define JSON_TYPE_SEND_GPS_LOCAL_SUCCESS 31
#define JSON_TYPE_SEND_GPS_LOCAL_FAIL 32
#define JSON_TYPE_RECEIVE_GPS_LOCAL 33
#define JSON_TYPE_RECEIVE_RADIO_GPS 90
#define JSON_TYPE_ERROR 404
class StransforLayerCommunication : public QObject
{
    Q_OBJECT
public:
    explicit StransforLayerCommunication(QObject *parent = 0);

signals:
    void sendMessageSignal(QByteArray &data, QHostAddress &host,quint16 port);
    void sendUserMessagesSignal(char *,int, char * ,int);
    //void sendUserMessagesStatusSignal(char *, int);
public slots:
    void sendMessagesSlot();
    void receiveMessages(char *buff, int len);
    void SendMessagesState(char* str, int len,int state, int tx);
    void haveMessagesToStransforSlot(unsigned char *buff, int len);
    void updateRxValue(int v);
    void haveGPSToStransforSlot(QString co, QString lo, QString la, QString utcTime);
private:
    QTimer m_SendTimer;
    QJsonDocument json;
    QJsonDocument json_Messages;
    int rx_value;
    char tmpCh[4096];
};

#endif // STRANSFORLAYERCOMMUNICATION_H
