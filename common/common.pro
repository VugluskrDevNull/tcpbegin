TARGET = common
TEMPLATE = lib

QT -= gui
QT += network

CONFIG -= app_bundle
CONFIG += c++17
CONFIG += staticlib create_prl

DESTDIR = ..

SOURCES += \
        console.cpp

HEADERS += \
    Interface.h \
    console.h
