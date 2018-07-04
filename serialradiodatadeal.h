#ifndef SERIALRADIODATADEAL_H
#define SERIALRADIODATADEAL_H
#include <QObject>
#include <QThread>

class SerialRadioDataDeal : public QThread
{
    Q_OBJECT
public:
    SerialRadioDataDeal();
    void getDate(char * tmp, int count);
protected:
    void run();
signals:
    void RadioCommunicationSignal(char *, int );

};

#endif // SERIALRADIODATADEAL_H
