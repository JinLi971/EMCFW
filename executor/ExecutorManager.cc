#include "ExecutorManager.hh"

#include "IExecutable.hh"
#include "dataset/Constants.hh"
#include <cassert>

namespace Executor
{

std::unique_ptr<ExecutorManager> ExecutorManager::mInstance = nullptr;

ExecutorManager::ExecutorManager()
{
}

ExecutorManager::~ExecutorManager()
{
}

ExecutorManager *ExecutorManager::getInstance()
{
    if(mInstance.get() == nullptr)
    {
        mInstance.reset(new ExecutorManager());
    }
    return mInstance.get();
}

void ExecutorManager::destoryManager()
{
    destory();
    // This will call deconstructor
    mInstance = nullptr;
}

void ExecutorManager::destory()
{
    unsigned int retryTimes = 0;
    while (retryTimes < DataSet::RETRY_LIMIT)
    {
        bool running = false;
        std::vector<IExecutor::IExecutorPtr>::iterator iter = mList.begin();
        while(iter != mList.end())
        {
            IExecutor::IExecutorPtr& ele = *iter;
            assert(ele.use_count() == 1);
            ele->stop();
            if((*iter)->getExecutionState() == STOPPED)
            {
                ele.reset();
                iter = mList.erase(iter);
                continue;
            }
            running = true;
            ++ iter;

        }

        if (!running)
            break;

        retryTimes ++;
    }

    if(retryTimes == DataSet::RETRY_LIMIT)
    {
        fprintf(stderr, "FAILED to stop [%zu] executors, force delete, may have memory leak!\n", mList.size());
    }

    mList.erase(mList.begin(), mList.end());
}


void ExecutorManager::addExecutor(IExecutor::IExecutorPtr &instance)
{
    std::lock_guard<std::mutex> lock(mMutex);
    mList.push_back(instance);
    instance->setId(mList.size() - 1);
}

void ExecutorManager::handleExecutorStateChange(ExecutionState state,
                                                int id)
{
    switch(state)
    {
    case IDLE:
    case ERROR:
    case STOPPED:
    {
        dispatchJob(mList[id]);
        break;
    }
    default:
    {
        return;
    }
    }
}

void ExecutorManager::dispatchJob(IExecutor::IExecutorPtr &instance)
{
    if(mRequestQueue.empty())
    {
        return;
    }


    std::lock_guard<std::mutex> lock(mDispatchMutex);

    std::list<IExecutable*>::iterator iter = mRequestQueue.begin();

    while(iter != mRequestQueue.end())
    {
        IExecutable* callback = *iter;

        if(callback->getRequiredExecutorType() == instance->getType())
        {
            // match the type of calling
            if(callback->readyExecutor(instance))
            {
                mRequestQueue.erase(iter);
                return;
            }
        }

        ++iter;
    }
}

bool ExecutorManager::getExecutor(IExecutable *callBackInstance)
{
    std::lock_guard<std::mutex> lock(mDispatchMutex);
    std::list<IExecutable*>::iterator iter = mRequestQueue.begin();

    while(iter != mRequestQueue.end())
    {
        IExecutable* waitingEle = *iter;
        if(waitingEle->getRequiredExecutorType() == callBackInstance->getRequiredExecutorType())
        {
            mRequestQueue.push_back(callBackInstance);
            return true;
        }

        ++ iter;
    }

    for(unsigned int i = 0; i < mList.size(); ++ i)
    {
        if(mList[i]->getType() != callBackInstance->getRequiredExecutorType())
            continue;

        ExecutionState state = mList[i]->getExecutionState();
        if(state == IDLE || state == ERROR || state == STOPPED || state == WAITING)
        {
            if(callBackInstance->readyExecutor(mList[i]))
            {
                return true;
            }
        }
    }

    // No executor available for now
    // Put into waiting queue
    mRequestQueue.push_back(callBackInstance);
    return false;
}

int ExecutorManager::getSizeofExecutors(ExecutorType type)
{
    int count = 0;
    for(unsigned int i = 0; i < mList.size(); ++ i)
    {
        if(mList[i]->getType() == type)
            count ++;
    }

    return count;
}




}
