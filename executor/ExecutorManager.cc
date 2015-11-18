#include "ExecutorManager.hh"

#include "IExecutable.hh"
#include "dataset/Constants.hh"
namespace Executor
{

ExecutorManager::ExecutorManager()
{
}

ExecutorManager::~ExecutorManager()
{

}

ExecutorManager *ExecutorManager::getInstance()
{
    if(instance)
        return instance;

    instance = new ExecutorManager();
    return instance;
}

void ExecutorManager::destoryManager()
{
    destory();
    instance->~ExecutorManger();
}

void ExecutorManager::destory()
{
    unsigned int retryTimes = 0;
    while (retryTimes < DataSet::RETRY_LIMIT)
    {
        bool running = false;
        std::vector<IExecutor*>::iterator iter = mList.begin();
        while(iter != mList.end())
        {
            (*iter)->abort();
            if((*iter)->getExecutionState() == STOPPED)
            {
                delete (*iter);
                iter = mList.erase(iter);
                continue;
            }

            ++ iter;
            running = true;
        }

        if (!running)
            break;

        retryTimes ++;
    }

    if(retryTimes == DataSet::RETRY_LIMIT)
    {
        fprintf(stderr, "FAILED to stop [%d] executors, force delete, may have memory leak!\n", mList.size());
    }

    mList.erase(mList.begin(), mList.end());
}


void ExecutorManager::addExecutor(IExecutor* instance)
{
    instance->setNotifyHandler(&ExecutorManager::handleExecutorStateChange, this);
    mList.push_back(instance);
}

void ExecutorManager::handleExecutorStateChange(ExecutionState state,
                                                IExecutor* instance,
                                                void* handler)
{
    ExecutorManager *self = static_cast<ExecutorManager *>(handler);
    switch(state)
    {
        case IDLE:
        case ERROR:
        case STOPPED:
        {
            self->dispatchJob(instance);
            break;
        }
        default:
        {
            return;
        }
    }
}

void ExecutorManager::dispatchJob(IExecutor* instance)
{
    if(mRequestQueue.empty())
    {
        return;
    }

    mDispatchMutex.lock();

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
                mDispatchMutex.unlock();
                return;
            }
        }

        ++iter;
    }

    mDispatchMutex.unlock();
}

bool ExecutorManager::getExecutor(IExecutable *callBackInstance)
{
    std::list<IExecutable*>::iterator iter = mRequestQueue.begin();

    while(iter != mRequestQueue.end())
    {
        IExecutable* waitingEle = *iter;
        if(waitingEle->getRequiredExecutorType() == callBackInstance->getRequiredExecutorType())
        {
            mMutex.lock();
            mRequestQueue.push_back(callBackInstance);
            mMutex.unlock();
            return;
        }

        ++ iter;
    }

    mMutex.lock();

    for(unsigned int i = 0; i < mList.size(); ++ i)
    {
        if(mList[i]->getType() != callBackInstance->getRequiredExecutorType())
            continue;

        ExecutionState state = mList[i]->getExecutionState();
        if(state == IDLE || state == ERROR || state == STOPPED)
        {
            if(callBackInstance->readyExecutor(mList[i]))
            {
                mMutex.unlock();
                return true;
            }
        }
    }

    // No executor available for now
    // Put into waiting queue
    mRequestQueue.push_back(callBackInstance);

    mMutex.unlock();

    return false;
}




}
