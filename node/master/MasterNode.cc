#include "MasterNode.hh"
#include "utils/comm/icommunication.h"
//#include <libconfig.h++>
#include "dispatcher/Dispatcher.hh"

namespace Node
{
namespace Master
{

MasterNode::MasterNode()
    : mTaskId(-1)
{
}

int MasterNode::getTaskId()
{
    return mTaskId;
}

void MasterNode::setTaskId(int value)
{
    mTaskId = value;
}

void MasterNode::init()
{
    // Master Node will load the master.conf file in
    loadMasterConf();
}

void MasterNode::dispatchJob()
{
    // Apply different job dispatch strategies.
    Dispatcher::Dispatcher dispatcher = Dispatcher::DispatcherFactory::getDispatcher(Dispatcher::DispatcherFactory::EVEN,
                                                                         mConf,
                                                                         mSlaveList,
                                                                         *this);
    dispatcher.apply();
}

void MasterNode::loadData()
{
    // Do nothing
}

void MasterNode::loadMasterConf()
{
    // Read conf from the config file under the same dir of binary
    /*Config config;
    try
    {
        config.readFile("./emc.conf");
    }
    catch (FileIOException& e)
    {
        fprintf(stderr, "FileIOException Error: %s\n", e.what());
        exit(1);
    }
    catch (ParseException& ee)
    {
        fprintf(stderr, "ParseException Error: %d - %s\n", ee.getLine(), ee.getError());
        exit(1);
    }

    config.lookupValue("DataDir", mConf.dataFileDir);
    config.lookupValue("StartIndex", mConf.dataStartIndex);
    config.lookupValue("EndIndex", mConf.dataEndIndex);
    config.lookupValue("Dispatcher", mConf.dispatchStrategy);*/
}

}
}

