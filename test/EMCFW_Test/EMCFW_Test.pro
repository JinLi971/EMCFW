#-------------------------------------------------
#
# Project created by QtCreator 2015-11-08T21:19:26
#
#-------------------------------------------------

QT       -= core

QT       -= gui

TARGET = EMCFW_Test
CONFIG   += console
CONFIG   -= app_bundle
QMAKE_CXXFLAGS += -std=c++11
QMAKE_CC = mpicc
QMAKE_CXX = mpic++
QMAKE_LINK = mpic++

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
#INCLUDEPATH += /opt/openmpi/include
DEPENDPATH += /usr/include/

PRE_TARGETDEPS += /usr/local/lib/libgtest.a

HEADERS += \
    Serialization/TestSerialization.hh \
    Mpi/TestMpiConnection.hh
