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
    node/slave/SlaveNode.cc \
    executor/cuda/CudaExecutor.cc \
    dataset/executor/cuda/CudaContext.cc \
    dataset/executor/cuda/CudaResult.cc \
    executor/MockExecutor.cc \
    dataset/executor/MockContextAndResult.cc \
    executor/ExecutorManager.cc \
    executor/ExecutorFactory.cc \
    dataset/control/NodeInstructionData.cc \
    dataset/executor/ContextAndResultFactory.cc


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
    dataset/Constants.hh \
    executor/IExecutor.hh \
    executor/cuda/CudaExecutor.hh \
    dataset/executor/cuda/CudaContext.hh \
    dataset/executor/cuda/CudaResult.hh \
    executor/MockExecutor.hh \
    dataset/executor/MockContextAndResult.hh \
    executor/ExecutorManager.hh \
    dataset/executor/IContext.hh \
    dataset/executor/IResult.hh \
    executor/IExecutable.hh \
    executor/ExecutorFactory.hh \
    dataset/executor/ExecutorType.hh \
    dataset/control/NodeInstructionData.hh \
    dataset/executor/ContextAndResultFactory.hh

LIBS += -L/usr/local/lib64/ -lspimage
LIBS += -L/usr/lib/ -lmpi
LIBS += -L/usr/lib/x86_64-linux-gnu -lconfig++

LIBS += -L/home/exuugag/devApp/openmpi/lib -lmpi
LIBS += -L/home/exuugag/devApp/libconfig/lib -lconfig++


INCLUDEPATH += /usr/local/include/spimage \
    /usr/local/include \
    /usr/include/mpi/ \
    /home/exuugag/devApp/openmpi/include \
    /home/exuugag/Jing/libspimage/libspimage/include \
    /home/exuugag/devApp/libconfig/include

DEPENDPATH += /usr/local/include/spimage \
   /usr/local/include

unix {
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES +=

