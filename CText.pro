#-------------------------------------------------
#
# Project created by QtCreator 2014-09-08T13:55:27
#
#-------------------------------------------------

QT       += core gui
QT       += network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CText
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myserver.cpp \
    mythread.cpp

HEADERS  += mainwindow.h \
    myserver.h \
    mythread.h

FORMS    += mainwindow.ui
