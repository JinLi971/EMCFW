#-------------------------------------------------
#
# Project created by QtCreator 2015-11-08T21:19:26
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = EMCFW_Test
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c11

TEMPLATE = app


SOURCES += main.cc \
    Serialization/TestSerialization.cc

LIBS += -L$$PWD/../../../build-EMCFW-Desktop-Debug/ -lEMCFW

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../

unix:!macx: LIBS += -L/usr/lib/ -lgtest

INCLUDEPATH += /usr/include/gtest
DEPENDPATH += /usr/include/gtest

unix:!macx: PRE_TARGETDEPS += /usr/lib/libgtest.a

HEADERS += \
    Serialization/TestSerialization.hh
