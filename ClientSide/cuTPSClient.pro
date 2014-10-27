#-------------------------------------------------
#
# Project created by QtCreator 2014-10-15T11:42:18
#
#-------------------------------------------------

QT       += core gui widgets
QT      += network


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
    ../Common/course.cpp

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
    ../Common/course.h
