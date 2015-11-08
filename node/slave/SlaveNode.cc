#include "SlaveNode.hh"
#include <assert.h>
#include "dataset/Constants.hh"

namespace Node
{
namespace Slave
{

SlaveNode::SlaveNode(int taskId)
    : mTaskId(taskId)
{
}

int SlaveNode::getTaskId() const
{
    return mTaskId;
}

void SlaveNode::setTaskId(int value)
{
    assert(value > 1);
    mTaskId = value;
}

const DataSet::Control::LoadSpec &SlaveNode::getLoadSpec()
{
    return mLoadSpec;
}

void SlaveNode::setLoadSpec(const DataSet::Control::LoadSpec &loadSpec)
{
    mLoadSpec = loadSpec;
}

void SlaveNode::dispatchJob()
{
    mConnection.setMode(IComm::REC);
    // LoadSpec can only be sent from root
    mConnection.sync(&mLoadSpec, -1, -1, DataSet::ROOT_ID);
    // Sync nodes in order to start correctly
    mConnection.barrier();
}

void SlaveNode::init()
{

}

void SlaveNode::loadData()
{

}

}
}
