#-------------------------------------------------
#
# Project created by QtCreator 2018-04-16T10:54:00
#
#-------------------------------------------------

QT       += core
QT       += network
QT       += serialport

QT       -= gui

TARGET = test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    readconfigfile.cpp \
    mainworkflow.cpp \
    udpsocket.cpp \
    radiocommunication.cpp \
    physicallayercommunication.cpp \
    stransforlayercommunication.cpp \
    queryfrequency.cpp \
    shiftantenna.cpp \
    serialport.cpp \
    serialradiodatadeal.cpp

HEADERS += \
    readconfigfile.h \
    mainworkflow.h \
    globalVariable.h \
    udpsocket.h \
    stransforlayercommunication.h \
    radiocommunication.h \
    physicallayercommunication.h \
    queryfrequency.h \
    shiftantenna.h \
    serialport.h \
    serialradiodatadeal.h



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/Olivia/release/ -lOlivia
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/Olivia/debug/ -lOlivia
else:unix: LIBS += -L$$PWD/Olivia/ -lOlivia

INCLUDEPATH += $$PWD/Olivia
DEPENDPATH += $$PWD/Olivia

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/Olivia/release/ -lOliviaAlsa
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/Olivia/debug/ -lOliviaAlsa
else:unix: LIBS += -L$$PWD/Olivia/ -lOliviaAlsa

INCLUDEPATH += $$PWD/Olivia
DEPENDPATH += $$PWD/Olivia
