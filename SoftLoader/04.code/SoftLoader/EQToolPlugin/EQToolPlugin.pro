# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------
QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport serialport
CONFIG += c++11

TEMPLATE = lib
TARGET = EQToolPlugin
DESTDIR = ../Bin/Plugin
CONFIG += release
DEFINES += EQTOOLPLUGIN_LIB
LIBS += -L"."
DEPENDPATH += .
MOC_DIR += .
OBJECTS_DIR += release
UI_DIR += .
RCC_DIR += .
HEADERS += ./eqtoolplugin_global.h \
    ./EQTools.h \
    ./EQToolPlugin.h \
    ../common/serialport/HandleCom.h \
    ../common/serialport/SerialPortDlg.h \
    ../common/customplot/QEQLinesChart.h \
    ../common/customplot/QAbstractDynamicLinesChart.h \
    ../common/customplot/qcustomplot.h \
    ../common/datastruct/DataStruct_anc_eq.h \
    ../common/datastruct/FrequencySpectrum.h \
    ../3rd/waveAlgorithm/skv_wolf_function.h
SOURCES += ./EQTools.cpp \
    ./EQToolPlugin.cpp \
    ../common/serialport/HandleCom.cpp \
    ../common/serialport/SerialPortDlg.cpp \
    ../common/customplot/QAbstractDynamicLinesChart.cpp \
    ../common/customplot/qcustomplot.cpp \
    ../common/customplot/QEQLinesChart.cpp \
    ../common/datastruct/FrequencySpectrum.cpp \
    ../3rd/waveAlgorithm/skv_wolf_function.c
FORMS += ../common/serialport/SerialPortDlg.ui \
    ./EQTools.ui
RESOURCES += ANCTool.qrc
