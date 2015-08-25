#-------------------------------------------------
#
# Project created by QtCreator 2015-04-23T15:51:02
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += sql
QT       += network
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = src
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    lib/class_sqlite.cpp \
    lib/class_string.cpp

HEADERS  += mainwindow.h \
    lib/class_sqlite.h \
    lib/class_string.h \
    TSCLIB.h

FORMS    += mainwindow.ui

DISTFILES += \
    ../README.txt \
    ../build-src-Desktop_Qt_5_4_1_MinGW_32bit-Release/config.ini.txt \
    ../build-src-Desktop_Qt_5_4_1_MinGW_32bit-Release/config.ini
