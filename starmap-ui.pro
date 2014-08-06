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
    mappixmapitem.cpp \
    cli_tools/planet.cpp \
    cli_tools/player.cpp

HEADERS  += starmapui.h \
    cli_tools/map.h \
    cli_tools/star.h \
    cli_tools/util.h \
    mappixmapitem.h \
    cli_tools/planet.h \
    cli_tools/startype.h \
    cli_tools/player.h

FORMS    += starmapui.ui

OTHER_FILES += \
    starpics/bluedwarf.png \
    starpics/bluegiant.png \
    starpics/bluesupergiant.png \
    starpics/blue-violetdwarf.png \
    starpics/blue-violetgiant.png \
    starpics/blue-violetsupergiant.png \
    starpics/blue-whitedwarf.png \
    starpics/nostar.png \
    starpics/orangedwarf.png \
    starpics/reddwarf.png \
    starpics/redgiant.png \
    starpics/redsupergiant.png \
    starpics/whitedwarf.png \
    starpics/yellowdwarf.png \
    starpics/yellowsupergiant.png
