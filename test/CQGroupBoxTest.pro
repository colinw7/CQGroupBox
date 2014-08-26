TEMPLATE = app

TARGET = CQGroupBoxTest

QT += widgets

DEPENDPATH += .

#CONFIG += debug

# Input
SOURCES += \
CQGroupBoxTest.cpp \

HEADERS += \
CQGroupBoxTest.h \

DESTDIR     = .
OBJECTS_DIR = .

INCLUDEPATH += \
../include \
.

unix:LIBS += \
-L../lib \
-lCQGroupBox
