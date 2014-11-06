#-------------------------------------------------
#
# Project created by QtCreator 2014-10-15T11:42:18
#
#-------------------------------------------------

QT       += core gui
QT      += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cuTPSClient

TEMPLATE = app


SOURCES += main.cpp \
    clientconnection.cpp \
    logincontroller.cpp \
    cutpsclient.cpp \
    studentcontroller.cpp \
    ../Common/student.cpp \
    ../Common/user.cpp \
    ../Common/contentmanager.cpp \
    ../Common/administrator.cpp \
    ../Common/item.cpp \
    ../Common/book.cpp \
    ../Common/chapter.cpp \
    ../Common/section.cpp \
    ../Common/course.cpp \
    ../Common/Cart.cpp \
    cmcontroller.cpp

FORMS += \
    loginPage.ui

HEADERS += \
    clientconnection.h \
    logincontroller.h \
    cutpsclient.h \
    studentcontroller.h \
    ../Common/student.h \
    ../Common/user.h \
    ../Common/contentmanager.h \
    ../Common/administrator.h \
    ../Common/item.h \
    ../Common/book.h \
    ../Common/chapter.h \
    ../Common/section.h \
    ../Common/course.h \
    ../Common/cart.h \
    cmcontroller.h
