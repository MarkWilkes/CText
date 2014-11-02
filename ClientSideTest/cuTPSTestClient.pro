#-------------------------------------------------
#
# Project created by QtCreator 2014-11-01T21:22:36
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cuTPSTestClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    clientconnection.cpp

HEADERS  += mainwindow.h \
    clientconnection.h

FORMS    += mainwindow.ui
