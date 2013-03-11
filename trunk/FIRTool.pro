#-------------------------------------------------
#
# Project created by QtCreator 2013-03-01T16:06:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4) : QT += widgets
greaterThan(QT_MAJOR_VERSION, 4) : QT *= printsupport

TARGET = FIRTool
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    windowCheby.cpp \
    freqchar.cpp \
    filters.cpp \
    fftw.cpp \
    windowKaiser.cpp \
    windowHarris.cpp

HEADERS  += \
    mainwindow.h \
    qcustomplot.h \
    fftw3.h \
    filters.h \
    fftw.h

FORMS    += mainwindow.ui

win32: {
    LIBS += -L$$PWD -lfftw3-3
}

macx : {
    LIBS += -L$$PWD/../../../../opt/local/lib/ -lfftw3
    INCLUDEPATH += $$PWD/../../../../opt/local/include
    DEPENDPATH += $$PWD/../../../../opt/local/include
    PRE_TARGETDEPS += $$PWD/../../../../opt/local/lib/libfftw3.a
}

RESOURCES += \
    firtool.qrc
