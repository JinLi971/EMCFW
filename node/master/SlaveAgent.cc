#include "SlaveAgent.hh"
#include "node/NodeUtils.hh"
#include <mpi.h>

namespace Node {
namespace Master {

SlaveAgent::SlaveAgent(const int taskId)
    : mTaskId(taskId)
{

}


void SlaveAgent::setLoadSpec(const DataSet::Control::LoadSpec &loadSpec)
{
    mLoadSpec = loadSpec;
}

void SlaveAgent::init()
{
    // Do nothing
}

void SlaveAgent::dispatchJob()
{
    // Send the loadSpec to the slave node
    // the slaveAgent has the same taskId of the slave
    mCommunicator.setMode(IComm::SEND);
    mCommunicator.sync(&mLoadSpec, mTaskId);
    mCommunicator.barrier();

    Utils::GroupHelpers::constructGroup(mLoadSpec, mTaskId);
}

void SlaveAgent::loadData()
{
    // Do nothing
}

}
}
