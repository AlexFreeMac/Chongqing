#-------------------------------------------------
#
# Project created by QtCreator 2018-04-16T10:54:00
#
#-------------------------------------------------

QT       += core
QT       += network

QT       -= gui

TARGET = test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    readconfigfile.cpp \
    radioconmunication.cpp \
    mainworkflow.cpp \
    stransforlayerconmunication.cpp

HEADERS += \
    readconfigfile.h \
    radioconmunication.h \
    mainworkflow.h \
    stransforlayerconmunication.h \
    globalVariable.h
