#include "stransforlayercommunication.h"
#include "globalVariable.h"
#include "QDebug"
#include "QTime"
#include "QDateTime"
#include <QThread>
#include "stdio.h"
StransforLayerCommunication::StransforLayerCommunication(QObject *parent) :
    QObject(parent)
{
    qDebug()<<__FUNCTION__<<"CurrentThread"<<QThread::currentThread();
    connect(&m_SendTimer,SIGNAL(timeout()),this,SLOT(sendMessagesSlot()));
    //m_SendTimer.start(2000);
    rx_value = 0;
}



void StransforLayerCommunication::sendMessagesSlot()
{
    QString test="qiuhong,qiuhong";
    QByteArray cstr = test.toLatin1();
    //char *data;
    //data = test.toLatin1().data();

    QHostAddress address;
    address.setAddress(g_strTransforIP);
    emit sendMessageSignal(cstr,address,g_TransportUdpPort);
}

void StransforLayerCommunication::receiveMessages(char *buff, int len)
{
    QJsonParseError jsonError;
    QByteArray data = QByteArray(buff,len);
    //json = QJsonDocument::fromRawData(buff,len);
    json = QJsonDocument::fromJson(data, &jsonError);
    QJsonDocument json1;
    //json = QJsonDocument::from
    qDebug()<<QString::fromLatin1(buff,len)<<buff[0]<<buff[len-1];
    if(jsonError.error == QJsonParseError::NoError)
    {
        if(json.isObject())
        {
            QJsonObject rootobj = json.object();

            if(rootobj.contains("type"))
            {
                int type = 0;
                QJsonValue value = rootobj.value("type");
                type = value.toString().toInt();
                qDebug()<<"type:"<<type;
                switch (type)
                {
                case JSON_TYPE_SEND_MESSAGES:
                case JSON_TYPE_SEND_LOCAL_REQUEST:
                case JSON_TYPE_SEND_GPS_LOCAL:
                    {
//                        int tx = 0;
//                        value = rootobj.value("tx");
//                        tx = value.toInt();
//                        QString sender;
//                        value = rootobj.value("sender");
//                        sender = value.toString();
//                        QString receiver;
//                        value = rootobj.value("receiver");
//                        receiver = value.toString();
//                        QString message;
//                        value = rootobj.value("message");
//                        message = value.toString();
//                        char *messagebuff = message.toLatin1().data();
////                        sender = value.toInt();
//                        qDebug()<<"sender:"<<sender<<"receiver:"<<receiver<<"message:"<<message<<"messagebuff len"<<message.toLatin1().count();
//                        //QString buffstr;
                        value = rootobj.value("buffer");
                        qDebug()<<"buffstr"<<value.isArray()<<value.toArray().size();
                        QJsonArray jsonArray = value.toArray();
                        QByteArray messageArray;
                        qDebug()<<"encode :";
                        for(int i = 0 ; i < jsonArray.size(); i++)
                        {
                            char tmp = jsonArray.at(i).toInt() & 0x000000ff ;
                            messageArray.append(tmp);
                            printf("0X%02X ",(unsigned char) tmp);
                        }
                        printf("\n");

                        //char *tmp = messageArray.data();
                        qDebug()<<"messageArray"<<messageArray.count();
                        for(int i = 0 ; i<messageArray.count();i++)
                        {
                            tmpCh[i] = messageArray.at(i);
                        }
                        emit sendUserMessagesSignal(buff, len, tmpCh, messageArray.count());
                        //SendMessagesState(buff,len,1);

                    }
                    break;
                case JSON_TYPE_MESSAGES_RECEIVE:
                    {
                        int rx = 0;
                        value = rootobj.value("rx");
                        rx = value.toInt();
                    }
                    break;

                case JSON_TYPE_SEND_LOCAL_REQUEST_SUCCESS:

                    break;
                case JSON_TYPE_SEND_LOCAL_REQUEST_FAIL:

                    break;
                case JSON_TYPE_RECEIVE_LOCAL:

                    break;

                case JSON_TYPE_SEND_GPS_LOCAL_SUCCESS:

                    break;
                case JSON_TYPE_SEND_GPS_LOCAL_FAIL:

                    break;
                case JSON_TYPE_RECEIVE_GPS_LOCAL:

                    break;
                case JSON_TYPE_RECEIVE_RADIO_GPS:

                    break;
                case JSON_TYPE_ERROR:

                    break;
                default:
                    break;
                }
            }
            else
            {
                qDebug()<<"Type error!!";
            }
        }
        else
        {
            qDebug()<<"Json error!!";
        }
    }
    else
    {
        qDebug()<<"Json error First";
    }

}

void StransforLayerCommunication::SendMessagesState(char* str, int len,int state,int tx)
{
    QJsonParseError jsonError;
    QByteArray data = QByteArray(str,len);
    qDebug()<<data.length()<<data;
    //json = QJsonDocument::fromRawData(buff,len);
    json_Messages = QJsonDocument::fromJson(data, &jsonError);

    QJsonObject rootobj = json_Messages.object();
    qDebug()<<"1111"<<rootobj.count();
    QJsonValue value = rootobj.value("type");
    int type = value.toString().toInt();
    rootobj.insert("tx",tx);
    if(state == 1)
    {
        rootobj.insert("type",type+1);
    }
    else
    {
        rootobj.insert("type",type+2);
    }

    QDateTime dateTime;
    dateTime = QDateTime::currentDateTimeUtc();
    QString timeStr = dateTime.toString("yyyy-MM-ddThh:mm:ss.zzzZ");
    qDebug()<<timeStr;
    rootobj.insert("dateTime",timeStr);
    qDebug()<<"2222"<<rootobj.count();

    json_Messages.setObject(rootobj);
    QByteArray byteArray = json_Messages.toJson();

    QHostAddress address;
    address.setAddress(g_strTransforIP);
    emit sendMessageSignal(byteArray, address, g_TransportUdpPort);
}

void StransforLayerCommunication::haveMessagesToStransforSlot(unsigned char *buff, int len)
{
    QJsonObject tmp_json;
    QJsonArray jsonBuffarray;
    for(int i = 0; i < len; i++)
    {
        jsonBuffarray.append(buff[i]);
    }
    tmp_json.insert("type",3);
    tmp_json.insert("rx",rx_value);
    tmp_json.insert("buffer",jsonBuffarray);
    QJsonDocument document;
    document.setObject(tmp_json);
    QByteArray jsonByteArray = document.toJson(QJsonDocument::Compact);
    qDebug()<<__FUNCTION__<<jsonByteArray;
    QHostAddress address;
    address.setAddress(g_strTransforIP);
    emit sendMessageSignal(jsonByteArray, address, g_TransportUdpPort);
}

void StransforLayerCommunication::updateRxValue(int v)
{
    rx_value = v;
    qDebug()<<__FUNCTION__<<"Rx:"<<rx_value;
}

void StransforLayerCommunication::haveGPSToStransforSlot(QString co, QString lo, QString la, QString utcTime)
{
    QJsonObject tmp_json;
    tmp_json.insert("type",90);
    tmp_json.insert("coordinate",co);
    tmp_json.insert("longitude",lo);
    tmp_json.insert("latitude",la);
    tmp_json.insert("utc",utcTime);
    QJsonDocument document;
    document.setObject(tmp_json);
    QByteArray jsonByteArray = document.toJson(QJsonDocument::Compact);
    qDebug()<<__FUNCTION__<<jsonByteArray;
    QHostAddress address;
    address.setAddress(g_strTransforIP);
    emit sendMessageSignal(jsonByteArray, address, g_TransportUdpPort);
}
