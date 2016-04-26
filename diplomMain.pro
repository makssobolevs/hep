TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

VPATH += ./src/
SOURCES += main.cpp \
        definitions.cpp \
        m1.cpp m2.cpp m3.cpp m4.cpp m5.cpp m6.cpp m7.cpp m8.cpp m9.cpp
VPATH += ./include/
HEADERS += definitions.h \
        m1.h m2.h m3.h m4.h m5.h m6.h m7.h m8.h m9.h
INCLUDEPATH = ./include/

OBJECTS_DIR = ../obj/

QMAKE_CXXFLAGS += -O3
