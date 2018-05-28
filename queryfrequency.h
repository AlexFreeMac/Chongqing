#ifndef QUERYFREQUENCY_H
#define QUERYFREQUENCY_H

#include <QObject>
#include <QHostAddress>
#include <QTimer>
class QueryFrequency : public QObject
{
    Q_OBJECT
public:
    explicit QueryFrequency(QObject *parent = 0);

signals:
    void queryFreqSignal(QByteArray &byteArray, QHostAddress &address,quint16 port);

public slots:
    void needQueryFreq();
    void OntimerToGetFreq();
private:
    QTimer getFreqTimer;
};

#endif // QUERYFREQUENCY_H
