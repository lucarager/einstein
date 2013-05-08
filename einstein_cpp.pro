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
    db.cpp \
    ind_checkbox.cpp \
    clues.cpp \
    table.cpp \
    cbox.cpp

HEADERS  += mainwindow.h \
    db.h \
    ind_checkbox.h \
    table.h \
    clues.h \
    cbox.h \
    tablecell.h

RESOURCES += \
    resources.qrc
