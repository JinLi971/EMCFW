#include "SlaveNode.hh"
#include <assert.h>
#include "dataset/Constants.hh"
#include "executor/ExecutorFactory.hh"

#include <unistd.h>
#include <thread>

namespace Node
{
namespace Slave
{

SlaveNode::SlaveNode(int taskId)
    : mTaskId(taskId)
{
    mState = IDLE;
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
    mState = IDLE;
}

void SlaveNode::loadData()
{
    assert(!mLoadSpec.getConfigFilePath().empty());
    assert(mLoadSpec.getControlId() != -1);

    IExecutor* executor = Executor::ExecutorFactory::getExecutor(mLoadSpec.getExecutorType());
    assert(executor);

    Executor::ExecutorManager::getInstance()->addExecutor(executor);
    waitForTask();
    mState = INITED;
}

void SlaveNode::start()
{
    // Get the executor
    Executor::ExecutorManager::getInstance()->getExecutor(this);

    // TODO: we are now single threaded, we can make multithread that needs some sync-waiting.
    mState = STARTED;
    for(int i = 0; i < mLoadSpec.getSmallIterationTime(); ++ i)
    {
        try
        {
            prepareExecutor();
            std::thread worker(&IExecutor::start, std::ref(*mExecutor));
            mState = RUNNING;
            worker.join();
        } catch (const std::exception& e) {
            mExecutor.reset();
            fprintf(stderr,
                    "Executor [%d] throws exception [%d] on Node [%d]: [%s]\n",
                    mExecutor->getType(),
                    DataSet::EXECUTOR_RUN_EXCEPTION,
                    mTaskId,
                    e.what());
            throw e;
        }
    }

    reportResultToClusterHead();
    cleanResource();
    waitForTask();
}

void SlaveNode::setContext(IContext *ctx)
{
    mContext.reset(ctx);
}

const IContext::ContextPtr &SlaveNode::getContext() const
{
    return mContext;
}

IContext::ContextPtr &SlaveNode::getContextRef()
{
    return mContext;
}

void SlaveNode::setResult(IResult *result)
{
    mResult.reset(result);
}

const IResult::ResultPtr &SlaveNode::getResult() const
{
    return mResult;
}

IResult::ResultPtr &SlaveNode::getResultRef()
{
    return mResult;
}

ExecutorType SlaveNode::getRequiredExecutorType()
{
    return mLoadSpec.getExecutorType();
}

bool SlaveNode::readyExecutor(IExecutor *instance)
{
    // We have a read-to-go executor

    // If it is not we want... forget about it.
    if(instance->getType() != mLoadSpec.getExecutorType())
        return false;

    mExecutor.reset(instance);
    instance->reserve();
    return true;
}

void SlaveNode::prepareExecutor()
{
    mExecutor->setContext(mContext);
    mExecutor->setResult(mResult);

    try
    {
        mExecutor->init();
    } catch (const std::exception& e) {
        mExecutor.reset();
        fprintf(stderr,
                "Executor [%d] throws exception [%d] on Node [%d]: [%s]\n",
                mExecutor->getType(),
                DataSet::EXECUTOR_INIT_EXCEPTION,
                mTaskId,
                e.what());
        exit(1);
    }
}

void SlaveNode::reportResultToClusterHead()
{
    // Lets report to clusterHead
    mConnection.setMode(IComm::SEND);
    mConnection.sync(mLoadSpec.getControlId(), -1, -1, true);
}

void SlaveNode::waitForTask()
{
    mState = IDLE;

    mConnection.setMode(IComm::REC);
    //mConnection.setData();
    mConnection.sync(-1, -1, mLoadSpec.getControlId());
}

void SlaveNode::cleanResource()
{
    mExecutor->resetToIdle();
    mExecutor.reset();

    mContext.reset();
    mResult.reset();
}



}
}
