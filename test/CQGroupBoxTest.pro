TEMPLATE = app

TARGET = CQGroupBoxTest

QT += widgets

DEPENDPATH += .

QMAKE_CXXFLAGS += -std=c++14

MOC_DIR = .moc

SOURCES += \
CQGroupBoxTest.cpp \

HEADERS += \
CQGroupBoxTest.h \

DESTDIR     = ../bin
OBJECTS_DIR = ../obj

INCLUDEPATH += \
. \
../include \
../../CQUtil/include \

unix:LIBS += \
-L../lib \
-L../../CQUtil/lib \
-L../../CConfig/lib \
-L../../CImageLib/lib \
-L../../CFont/lib \
-L../../CMath/lib \
-L../../CFileUtil/lib \
-L../../CFile/lib \
-L../../CUtil/lib \
-L../../CRegExp/lib \
-L../../CStrUtil/lib \
-L../../COS/lib \
-lCQGroupBox -lCQUtil \
-lCConfig -lCImageLib -lCFont -lCMath \
-lCFileUtil -lCFile -lCRegExp -lCStrUtil \
-lCUtil -lCOS \
-lpng -ljpeg -ltre
