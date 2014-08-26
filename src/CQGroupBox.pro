TEMPLATE = lib

TARGET = CQGroupBox

QT += widgets

DEPENDPATH += .

CONFIG += staticlib

# Input
HEADERS += \
../include/CQGroupBox.h \

SOURCES += \
CQGroupBox.cpp \

OBJECTS_DIR = ../obj

DESTDIR = ../lib

INCLUDEPATH += \
. \
../include \
