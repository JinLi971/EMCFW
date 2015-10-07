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
    dataset/control/Config.cc

HEADERS += \
    node/NodeConstants.hh \
    node/NodeFactory.hh \
    node/INode.hh \
    node/master/MasterNode.hh \
    dataset/Frame.hh \
    dataset/FrameList.hh \
    dataset/Model.hh \
    dataset/Mask.hh \
    dataset/control/Config.hh

unix: LIBS += -L/usr/local/lib64/ -lspimage

INCLUDEPATH += /usr/local/include/spimage \
    /usr/local/include
DEPENDPATH += /usr/local/include/spimage \
   /usr/local/include
