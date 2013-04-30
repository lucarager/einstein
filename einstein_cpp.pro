#-------------------------------------------------
#
# Project created by QtCreator 2013-04-25T13:08:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = einstein_cpp
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    cell.cpp \
    indications.cpp \
    db.cpp \
    ind_checkbox.cpp

HEADERS  += mainwindow.h \
    cell.h \
    indications.h \
    db.h \
    ind_checkbox.h

RESOURCES += \
    resources.qrc
