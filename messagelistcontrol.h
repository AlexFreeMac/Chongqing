#ifndef MESSAGELISTCONTROL_H
#define MESSAGELISTCONTROL_H

#include <QObject>
#include <QThread>
#include <QQueue>
class MessageListControl : public QThread
{
    Q_OBJECT
public:
    explicit MessageListControl();
protected:
    void run();
signals:
    void NeedSendMessagesToPhyLayer(char *, int );
public slots:
    void addMessagesToQueue(char *buff, int len);
    void nextMessages();
private:
    QQueue<char *> m_MesageQueue;
    QQueue<int> m_MssageCountQueue;
    char* m_preMessagePtr;
};

#endif // MESSAGELISTCONTROL_H
