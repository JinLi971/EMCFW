CONFIG -= qt
CONFIG += c11

QT       -= gui

TARGET = EMCFW
TEMPLATE = lib

QMAKE_CXXFLAGS += -std=c++11

DEFINES += EMCFW_LIBRARY

SOURCES += main.cpp \
    node/NodeFactory.cc \
    node/master/MasterNode.cc \
    dataset/Frame.cc \
    dataset/FrameList.cc \
    dataset/Model.cc \
    dataset/Mask.cc \
    dataset/control/LoadSpec.cc \
    node/master/dispatcher/EvenDispatcher.cc \
    node/master/MasterConf.cc \
    node/master/dispatcher/DispatcherBase.cc \
    utils/serializer/serializationbase.cpp \
    utils/serializer/SpImageSerializer.cpp \
    node/master/SlaveAgent.cc \
    utils/comm/mpiconnection.cc \
    node/slave/SlaveNode.cc

HEADERS += \
    node/NodeConstants.hh \
    node/NodeFactory.hh \
    node/INode.hh \
    node/master/MasterNode.hh \
    dataset/Frame.hh \
    dataset/FrameList.hh \
    dataset/Model.hh \
    dataset/Mask.hh \
    dataset/control/LoadSpec.hh \
    node/master/dispatcher/EvenDispatcher.hh \
    node/master/MasterConf.hh \
    node/master/dispatcher/DispatcherBase.hh \
    utils/comm/icommconfig.h \
    utils/comm/icommunication.h \
    utils/comm/mpiconnection.h \
    utils/serializer/serializationbase.h \
    utils/serializer/SpImageSerializer.h \
    utils/serializer/ISerializable.hh \
    utils/serializer/GlobalClassId.hh \
    node/master/SlaveAgent.hh \
    node/master/dispatcher/Dispatcher.hh \
    node/master/dispatcher/DispatcherFactory.h \
    node/slave/SlaveNode.hh \
    dataset/Constants.hh

LIBS += -L/usr/local/lib64/ -lspimage
LIBS += -L/usr/lib/ -lmpi
LIBS += -L/usr/lib/x86_64-linux-gnu -lconfig++

INCLUDEPATH += /usr/local/include/spimage \
    /usr/local/include \
   /usr/include/mpi/
DEPENDPATH += /usr/local/include/spimage \
   /usr/local/include

unix {
    target.path = /usr/lib
    INSTALLS += target
}

