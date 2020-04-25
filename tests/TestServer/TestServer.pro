#-------------------------------------------------
#
# Project created by QtCreator 2019-06-07T00:03:15
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestServer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lfftw3

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        ../../src/Libs/RTL_SDR_RadarLib/shared_classes/objects/air/StructAircraft.h \
        mainwindow.h

FORMS += \
        mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11
