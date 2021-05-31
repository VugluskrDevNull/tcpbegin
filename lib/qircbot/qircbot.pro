TARGET = qircbot
TEMPLATE = lib

QT -= gui
QT += network

CONFIG -= app_bundle
CONFIG += c++17
CONFIG += staticlib create_prl

DESTDIR = ../..

INCLUDEPATH += \
    ../../common

SOURCES += \
        qircbot.cpp

HEADERS += \
    ../../common/Interface.h \
    qircbot.h

