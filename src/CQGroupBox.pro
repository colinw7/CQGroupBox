TEMPLATE = lib

TARGET = CQGroupBox

QT += widgets

DEPENDPATH += .

QMAKE_CXXFLAGS += -std=c++14

MOC_DIR = .moc

CONFIG += staticlib

SOURCES += \
CQGroupBox.cpp \

HEADERS += \
../include/CQGroupBox.h \

OBJECTS_DIR = ../obj

DESTDIR = ../lib

INCLUDEPATH += \
. \
../include \
../../CQUtil/include \
