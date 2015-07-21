#-------------------------------------------------
#
# Project created by QtCreator 2015-07-14T11:24:20
#
#-------------------------------------------------

QT       += core gui serialport printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = briup
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mainwidget.cpp \
    blureffect.cpp \
    blurpicker.cpp \
    titlebar.cpp \
    widget.cpp \
    ledsimulation.cpp \
    imageitem.cpp \
    grapwidget.cpp \
    infarredsimulation.cpp \
    interinstruction.cpp \
    lcdsimlation.cpp \
    buttondemonstrate.cpp \
    timersimalation.cpp \
    fileutils.cpp \
    histroyfiledialog.cpp \
    humiditywindow.cpp \
    qcustomplot.cpp \
    temperaturemainwindow.cpp \
    item.cpp \
    picker.cpp \
    lightdemonstrate.cpp \
    portsimulation.cpp \
    shakesimulator.cpp \
    rfidsimulation.cpp \
    buzzersimulator.cpp \
    musicwidget.cpp \
    mylabel.cpp \
    pianowidget.cpp \
    frame.cpp \
    motordemonstrate.cpp \
    expcode.cpp \
    expknowledge.cpp \
    expprinciple.cpp \
    complex.cpp

HEADERS  += mainwindow.h \
    mainwidget.h \
    blureffect.h \
    blurpicker.h \
    titlebar.h \
    leddisplay.h \
    widget.h \
    ledsimulation.h \
    imageitem.h \
    grapwidget.h \
    infarredsimulation.h \
    interinstruction.h \
    lcdsimlation.h \
    buttondemonstrate.h \
    timersimalation.h \
    fileutils.h \
    histroyfiledialog.h \
    humiditywindow.h \
    qcustomplot.h \
    temperaturemainwindow.h \
    item.h \
    picker.h \
    lightdemonstrate.h \
    portsimulation.h \
    shakesimulator.h \
    rfidsimulation.h \
    buzzersimulator.h \
    musicwidget.h \
    mylabel.h \
    pianowidget.h \
    frame.h \
    motordemonstrate.h \
    expcode.h \
    expknowledge.h \
    expprinciple.h \
    complex.h

FORMS    += mainwindow.ui \
    mainwidget.ui \
    widget.ui \
    ledsimulation.ui \
    grapwidget.ui \
    infarredsimulation.ui \
    interinstruction.ui \
    lcdsimlation.ui \
    timersimalation.ui \
    histroyfiledialog.ui \
    humiditywindow.ui \
    temperaturemainwindow.ui \
    lightdemonstrate.ui \
    portsimulation.ui \
    shakesimulator.ui \
    rfidsimulation.ui \
    buzzersimulator.ui \
    musicwidget.ui \
    pianowidget.ui \
    buttondemonstrate.ui \
    motordemonstrate.ui \
    expcode.ui \
    expknowledge.ui \
    expprinciple.ui \
    complex.ui

RESOURCES += \
    images.qrc \

DISTFILES += \
    circuit_images/0001.jpg \
    circuit_images/0002.jpg \
    circuit_images/0003.jpg \
    circuit_images/0004.jpg \
    circuit_images/0005.jpg \
    circuit_images/0006.jpg \
    circuit_images/0007.jpg \
    circuit_images/0008.jpg \
    circuit_images/0009.jpg \
    circuit_images/0010.jpg \
    circuit_images/0011.jpg \
    circuit_images/0012.jpg \
    circuit_images/0013.jpg \
    circuit_images/0014.jpg

RC_FILE += app_icon.rc
