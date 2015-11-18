#include "SlaveNode.hh"
#include <assert.h>
#include "dataset/Constants.hh"
#include "executor/ExecutorFactory.hh"

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
    // Do nothing until receive the acutal loadSpec
}

void SlaveNode::loadData()
{
    assert(!mLoadSpec.getConfigFilePath().empty());
    assert(mLoadSpec.getControlId() != -1);

    IExecutor* executor = Executor::ExecutorFactory::getExecutor(mLoadSpec.getExecutorType());
    assert(executor);

    Executor::ExecutorManager::getInstance()->addExecutor(executor);
}

bool SlaveNode::readyExecutor(IExecutor *instance)
{
    // We have a read-to-go executor

    // If it is not we want... forget about it.
    if(instance->getType() != mLoadSpec.getExecutorType())
        return false;




}

}
}
