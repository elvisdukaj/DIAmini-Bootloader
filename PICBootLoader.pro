#-------------------------------------------------
#
# Project created by QtCreator 2016-01-11T10:33:43
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DIAload
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    utils.cpp \
    programoption.cpp \
    picfilesender.cpp \
    fakepicfilesender.cpp \
    aboutdialog.cpp

HEADERS  += mainwindow.h \
    utils.h \
    programoption.h \
    fakepicfilesender.h \
    picfilesender.h \
    aboutdialog.h

FORMS    += mainwindow.ui \
    aboutdialog.ui

RESOURCES += \
    resource.qrc

DISTFILES += \
    icon.rc

win32::RC_FILE = icon.rc
