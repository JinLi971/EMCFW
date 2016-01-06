#include "MasterNode.hh"
#include "utils/comm/icommunication.h"
#include <libconfig.h++>
#include "dispatcher/Dispatcher.hh"
#include "dispatcher/DispatcherFactory.h"

#include <memory>

namespace Node
{
namespace Master
{

MasterNode::MasterNode(int taskId)
    : mTaskId(taskId)
{
}

int MasterNode::getTaskId() const
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
    std::unique_ptr<Dispatcher::IDispatcher> dispatcher(Dispatcher::DispatcherFactory::getDispatcher(Dispatcher::DispatcherFactory::EVEN,
                                                                                                     mConf,
                                                                                                     mSlaveList,
                                                                                                     *this));
    dispatcher->apply();

    // Now dispatch all jobs to the slaves
    for(unsigned int i = 0; i < mSlaveList.size(); ++ i)
    {
        INode* slaveAgent = mSlaveList[i];
        slaveAgent->dispatchJob();
    }
}

const DataSet::Control::LoadSpec &MasterNode::getLoadSpec()
{
    return mEmptyLoadSpec;
}

void MasterNode::setLoadSpec(const DataSet::Control::LoadSpec &/*loadSpec*/)
{
    // Do nothing
}

void MasterNode::start()
{

}

void MasterNode::stop(int taskId)
{

}

bool MasterNode::destory()
{

}

void MasterNode::loadData()
{
    // Do nothing
}

void MasterNode::loadMasterConf()
{
    // Read conf from the config file under the same dir of binary
    libconfig::Config config;
    try
    {
        config.readFile("./emc.conf");
    }
    catch (libconfig::FileIOException& e)
    {
        fprintf(stderr, "FileIOException Error: %s\n", e.what());
        exit(1);
    }
    catch (libconfig::ParseException& ee)
    {
        fprintf(stderr, "ParseException Error: %d - %s\n", ee.getLine(), ee.getError());
        exit(1);
    }

    config.lookupValue("DataDir", mConf.dataFileDir);
    config.lookupValue("StartIndex", mConf.dataStartIndex);
    config.lookupValue("EndIndex", mConf.dataEndIndex);
    config.lookupValue("Dispatcher", mConf.dispatchStrategy);
}

}
}

