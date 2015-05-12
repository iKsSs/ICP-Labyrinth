#-------------------------------------------------
#
# Project created by QtCreator 2015-04-01T17:42:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = labyrinth2015
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tile.cpp \
    player.cpp \
    board.cpp \
    card.cpp

HEADERS  += mainwindow.h \
    tile.h \
    player.h \
    board.h \
    card.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
