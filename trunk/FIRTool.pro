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
    windowHarris.cpp \
    windowRifeVincent.cpp \
    remez.cpp \
    Newton_Real.cpp
#    zolotarevFIR.cpp

HEADERS  += \
    mainwindow.h \
    qcustomplot.h \
    fftw3.h \
    filters.h \
    fftw.h \
    windowRifeVincent.h \
    windowHarris.h \
    freqchar.h \
    windowCheby.h \
    windowKaiser.h \
    remez.h \
    double.h
#    zolotarevFIR.hpp

FORMS    += mainwindow.ui

RESOURCES += \
    firtool.qrc

win32 : {
    OTHER_FILES += firtool.rc
    RC_FILE = firtool.rc
}
macx : {
    ICON = toolbox.ico
}

win32 : {
    LIBS += -L$$PWD -lfftw3l-3
    QMAKE_LFLAGS += -static-libgcc -static-libstdc++
}

macx : {
    LIBS += -L/usr/local/lib/ -lfftw3l
    INCLUDEPATH += /usr/local/include
    DEPENDPATH += /usr/local/include
    PRE_TARGETDEPS += /usr/local/lib/libfftw3l.a
}

