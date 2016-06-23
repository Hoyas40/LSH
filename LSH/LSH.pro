#-------------------------------------------------
#
# Project created by QtCreator 2016-03-26T17:25:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LSH
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    calendarWidget.cpp \
    my_qlabel.cpp

HEADERS  += mainwindow.h \
    calendarWidget.h \
    my_qlabel.h

FORMS    += mainwindow.ui \
    calendarWidget.ui

RESOURCES += \
    rsc.qrc
