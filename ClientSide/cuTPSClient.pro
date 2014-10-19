#-------------------------------------------------
#
# Project created by QtCreator 2014-10-15T11:42:18
#
#-------------------------------------------------

QT       += core gui widgets
QT      += network


TARGET = cuTPSClient
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    clientconnection.cpp \
    logincontroller.cpp

FORMS += \
    loginPage.ui

HEADERS += \
    clientconnection.h \
    logincontroller.h
