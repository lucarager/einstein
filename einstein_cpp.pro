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
    db.cpp \
    ind_checkbox.cpp \
    clues.cpp \
    table.cpp

HEADERS  += mainwindow.h \
    cell.h \
    db.h \
    ind_checkbox.h \
    table.h \
    clues.h

RESOURCES += \
    resources.qrc
