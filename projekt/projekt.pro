#-------------------------------------------------
#
# Project created by QtCreator 2015-05-05T17:42:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projekt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tile.cpp \
    player.cpp \
    board.cpp

HEADERS  += mainwindow.h \
    tile.h \
    player.h \
    board.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
