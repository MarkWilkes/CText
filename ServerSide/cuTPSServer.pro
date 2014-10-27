#-------------------------------------------------
#
# Project created by QtCreator 2014-10-13T21:43:28
#
#-------------------------------------------------

QT       += core
QT       += network
QT       += gui

TARGET = cuTPSServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    Server/server.cpp \
    Server/serverconnection.cpp \
    Server/cutps.cpp \
    Server/accesscontrol.cpp \
    ../Common/student.cpp \
    ../Common/user.cpp \
    DataControl/datacontroller.cpp \
    ../Common/contentmanager.cpp \
    ../Common/administrator.cpp \
    ../Common/item.cpp \
    ../Common/book.cpp \
    ../Common/chapter.cpp \
    ../Common/section.cpp \
    ../Common/course.cpp

HEADERS += \
    Server/server.h \
    Server/serverconnection.h \
    Server/cutps.h \
    Server/accesscontrol.h \
    ../Common/student.h \
    ../Common/user.h \
    DataControl/datacontroller.h \
    DataControl/PersistImp.h \
    ../Common/contentmanager.h \
    ../Common/administrator.h \
    ../Common/item.h \
    ../Common/book.h \
    ../Common/chapter.h \
    ../Common/section.h \
    ../Common/course.h

OTHER_FILES += \
    Data/User.txt \
    Data/readMe.txt \
    Data/Books.txt \
    Data/Chapters.txt \
    Data/Sections.txt \
    Data/Courses.txt
