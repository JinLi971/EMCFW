TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

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
    node/master/SlaveAgent.cc

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
    node/master/dispatcher/Dispatcher.hh

unix: LIBS += -L/usr/local/lib64/ -lspimage

INCLUDEPATH += /usr/local/include/spimage \
    /usr/local/include \
   /usr/local/include/vtk-5.10/mrmpi \
   /usr/local/include/vtk-5.10/
DEPENDPATH += /usr/local/include/spimage \
   /usr/local/include \
   /usr/local/include/vtk-5.10/mrmpi \
   /usr/local/include/vtk-5.10/
