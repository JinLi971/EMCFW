#include "SlaveNode.hh"
#include <assert.h>
#include "dataset/Constants.hh"
#include "executor/ExecutorFactory.hh"
#include "node/NodeUtils.hh"
#include "dataset/executor/MockContextAndResult.hh"

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
    mConnection.setRank(mTaskId);

    mMpiWorldComm = MPI_COMM_WORLD;
}

SlaveNode::~SlaveNode()
{
    cleanResource();
    mLoadSpec.getSerializerRef().clearContent();
    mLoadSpec.getGroup().clear();
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

const DataSet::Control::LoadSpec &SlaveNode::getLoadSpec() const
{
    return mLoadSpec;
}

void SlaveNode::setLoadSpec(const DataSet::Control::LoadSpec &loadSpec)
{
    mLoadSpec = loadSpec;
}

void SlaveNode::init()
{
    // Do nothing until receive the loadSpec
}

void SlaveNode::dispatchJob()
{
    mConnection.setMode(IComm::REC);
    // LoadSpec can only be sent from root
    mConnection.sync(&mLoadSpec, -1, -1, DataSet::ROOT_ID);
    // Sync nodes in order to start correctly
    mConnection.barrier();
}

void SlaveNode::loadData()
{
    assert(!mLoadSpec.getConfigFilePath().empty());
    assert(mLoadSpec.getDefaultGroup() != -1);

    IExecutor::IExecutorPtr executor = Executor::ExecutorFactory::getExecutor(mLoadSpec.getExecutorType());
    assert(executor.get());

    executor->init();
    Executor::ExecutorManager::getInstance()->addExecutor(executor);

    //SlaveNode release executor
    executor.reset();

    Utils::GroupHelpers::constructGroup(mLoadSpec, mTaskId);
    mControlId = mLoadSpec.getGroupController(mLoadSpec.getDefaultGroup());

    if(mControlId == 0)
    {
        mConnection.setCommunicator(&mMpiWorldComm);
    }
    else
    {
        mConnection.setCommunicator(mLoadSpec.getGroupComm(mLoadSpec.getDefaultGroup()));
    }

    mState = INITED;
}

void SlaveNode::start()
{
    bool debug = true;
    while(debug)
    {
        mConnection.setMode(IComm::REC);
        mConnection.setData(&mCmd);
        mConnection.sync(-1, -1, mControlId);

        if(mCmd.getInstruction() & INode::DIE)
        {
            break;
        }

        if(mCmd.getInstruction() & INode::NEW_CONTEXT)
        {
            mContext = mCmd.getContextPtr();
        }

        if(mCmd.getInstruction() & INode::NEW_RESULT)
        {
            mResult = mCmd.getResultPtr();
        }

        if(mCmd.getInstruction() & INode::START)
        {
            startJob();
        }

        if(mCmd.getInstruction() & INode::REPORT)
        {
            reportResultToClusterHead();
        }
    }

    printf("SlaveNode [%d]: Finalizing...\n", mTaskId);
    destory();
    printf("SlaveNode [%d]: Exiting...\n", mTaskId);
}

void SlaveNode::stop(int taskId)
{
    if(taskId != mTaskId)
        return;

    if(mExecutor)
        mExecutor->stop();
}

bool SlaveNode::destory()
{
    stop(mTaskId);
    Executor::ExecutorManager::getInstance()->destoryManager();
    mState = DESTROIED;

    return true;
}

void SlaveNode::startJob()
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
            // TODO: Disable for now, because only single thread is supported in one slave node
//            std::thread worker(&IExecutor::start, std::ref(*mExecutor));
//            mState = RUNNING;
//            worker.join();
            mExecutor->start();
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

    // Retrieve the result
    mResult = mExecutor->getResult();

    cleanResource();
    mState = STOPPED;
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
int SlaveNode::getControlId() const
{
    return mControlId;
}

ExecutorType SlaveNode::getRequiredExecutorType()
{
    return mLoadSpec.getExecutorType();
}

bool SlaveNode::readyExecutor(IExecutor::IExecutorPtr& instance)
{
    // We have a read-to-go executor

    // If it is not we want... forget about it.
    if(instance->getType() != mLoadSpec.getExecutorType())
        return false;

    mExecutor = instance;
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
    mConnection.setData(mResult.get());
    mConnection.setMode(IComm::SSEND);
    mConnection.sync(mControlId, -1, -1, false);
}



void SlaveNode::cleanResource()
{
    if(mState == IDLE || mState == INITED) return;

    mState = IDLE;
    if(mExecutor)
    {
        mExecutor->resetToIdle();
        mExecutor.reset();
    }
}

}
}
