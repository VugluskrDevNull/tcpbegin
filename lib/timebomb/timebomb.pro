TARGET = timebomb

TEMPLATE = lib

QT -= gui

CONFIG -= app_bundle
CONFIG += c++1z
CONFIG += staticlib create_prl

DESTDIR = ../..

INCLUDEPATH += \
    ../../common

SOURCES += \
        timebomb.cpp

HEADERS += \
    ../../common/Interface.h \
    timebomb.h

