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
    table.cpp \
    clue_checkbox.cpp

HEADERS  += mainwindow.h \
    db.h \
    table.h \
    tablecell.h \
    clue_checkbox.h

RESOURCES += \
    resources.qrc
