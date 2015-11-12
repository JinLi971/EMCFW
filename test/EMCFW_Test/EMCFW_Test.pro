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
    Serialization/TestSerialization.cc \
    Mpi/TestMpiConnection.cc

LIBS += -L$$PWD/../../../build-EMCFW-Desktop-Debug/ -lEMCFW
LIBS += -L/usr/lib/ -lmpi

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../

unix:!macx: LIBS += -L/usr/lib/ -lgtest

INCLUDEPATH += /usr/include/
INCLUDEPATH += /usr/include/mpi
DEPENDPATH += /usr/include/

unix:!macx: PRE_TARGETDEPS += /usr/lib/libgtest.a

HEADERS += \
    Serialization/TestSerialization.hh \
    Mpi/TestMpiConnection.hh

OTHER_FILES +=
