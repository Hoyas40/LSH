#-------------------------------------------------
#
# Project created by QtCreator 2016-03-26T17:25:00
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LSH
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    calendarWidget.cpp \
    my_qlabel.cpp \
    dbmanager.cpp \
    editdbtabledialog.cpp \
    insertsubtabledialog.cpp \
    clientdialog.cpp \
    operationdialog.cpp \
    clientwidget.cpp

HEADERS  += mainwindow.h \
    calendarWidget.h \
    my_qlabel.h \
    dbmanager.h \
    databasetable.h \
    editdbtabledialog.h \
    insertsubtabledialog.h \
    clientdialog.h \
    operationdialog.h \
    clientwidget.h

FORMS    += mainwindow.ui \
    calendarWidget.ui \
    editdbtabledialog.ui \
    insertsubtabledialog.ui \
    clientdialog.ui \
    operationdialog.ui \
    clientwidget.ui

RESOURCES += \
    rsc.qrc
