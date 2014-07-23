#-------------------------------------------------
#
# Project created by QtCreator 2014-07-13T15:33:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = starmap-ui
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        starmapui.cpp \
    cli_tools/map.cpp \
    cli_tools/star.cpp \
    mappixmapitem.cpp

HEADERS  += starmapui.h \
    cli_tools/map.h \
    cli_tools/star.h \
    cli_tools/util.h \
    mappixmapitem.h

FORMS    += starmapui.ui