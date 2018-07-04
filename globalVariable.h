#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H
#include <QString>
#include <QSemaphore>
extern quint16 g_TransportUdpPort;
extern QString g_strTransforIP;
extern quint16 g_LocalUdpPort;
extern QString g_strLocalIP;
extern quint16 g_RadioStationUdpPort;
extern QString g_strRadioStationIP;
extern QString g_strGetFreqUdpIP;
extern quint16 g_GetFreqUdpPort;
extern bool g_isUseSerial;
extern char g_BUFF[1024];
extern int g_WriteIndex;
extern int g_ReadIndex;
extern QSemaphore g_freeBytes;
extern QSemaphore g_usedBytes;
#endif // GLOBALVARIABLE_H
