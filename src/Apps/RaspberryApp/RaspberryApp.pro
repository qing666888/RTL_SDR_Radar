#-------------------------------------------------
#
# Project created by QtCreator 2019-05-23T22:49:49
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RaspberryApp
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

CONFIG += c++11

include( ../../../common.pri )
include( ../../../app.pri )

RESOURCES += \
    ../../../import/res.qrc

DISTFILES += \
    ../../../import/style.qss

LIBS += -lLogger \
        -lPoolObject \
        -lCarrier \
        -lDataController \
        -lRTL_SDR_Reciver \
        -lDemodulator

SOURCES += \
    ../../Libs/RTL_SDR_RadarLib/shared_classes/widget/led/led.cpp \
    main.cpp \
    ui/Mainwindow.cpp \
    core/Core.cpp

HEADERS += \
    ../../Libs/RTL_SDR_RadarLib/shared_classes/widget/led/led.h \
    ../../include/interface/INetworkWorker.h \
    ui/Mainwindow.h \
    core/Core.h

FORMS += \
    ui/Mainwindow.ui
