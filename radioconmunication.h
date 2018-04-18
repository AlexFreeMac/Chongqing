#ifndef RADIOCONMUNICATION_H
#define RADIOCONMUNICATION_H

#include <QObject>
#include <QUdpSocket>
class RadioConmunication : public QObject
{
    Q_OBJECT
public:
    explicit RadioConmunication(QObject *parent = 0);
private:
signals:
    void SendCMDManualtune();
public slots:

};

#endif // RADIOCONMUNICATION_H
