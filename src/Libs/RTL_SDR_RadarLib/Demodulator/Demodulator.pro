#-------------------------------------------------
#
# Project created by QtCreator 2019-05-07T21:15:12
#
#-------------------------------------------------

QT       += gui

TARGET = Demodulator
TEMPLATE = lib

DEFINES += DEMODULATOR_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../../../import/osm/coordUtils/Conversions.cpp \
    ../../../../import/osm/coordUtils/Position.cpp \
        Demodulator.cpp \
    ../shared_classes/objects/base/BaseObject.cpp \
    ../shared_classes/objects/air/Aircraft.cpp

HEADERS += \
    ../../../../import/osm/coordUtils/Conversions.h \
    ../../../../import/osm/coordUtils/Position.h \
        ../../../include/interface/IDemodulator.h \
        ../../../include/Demodulator/Demodulator.h \
        ../../../include/Demodulator/demodulator_global.h \
    ../shared_classes/objects/base/BaseObject.h \
    ../shared_classes/objects/air/Aircraft.h \
    ../shared_classes/objects/air/StructAircraft.h \
    ../../../include/interface/IObject.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include( ../../../../common.pri )
include( ../../../../lib.pri )
