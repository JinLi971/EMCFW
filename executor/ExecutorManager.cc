#include "ExecutorManager.hh"
#include "dataset/Constants.hh"

namespace Executor
{

ExecutorManager::ExecutorManager()
{
}

void ExecutorManager::destory()
{
    int retryTimes = 0;
    while (retryTimes < DataSet::RETRY_LIMIT)
    {
        bool running = false;
        std::vector<IExecutor*>::iterator iter = mList.begin();
        while(iter != mList.end())
        {
            (*iter)->abort();
            if((*iter)->getExecutionState() == STOPPED)
            {
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
        fprintf(stderr, "FAILED to stop [%d] executors, force delete, may raise exception!\n", mList.size());
    }

    mList.erase(mList.begin(), mList.end());
}


void ExecutorManager::addExecutor(IExecutor* instance)
{
    instance->setNotifyHandler(&ExecutorManager::handleExecutorStateChange);
    mList.push_back(instance);
}

void ExecutorManager::handleExecutorStateChange(ExecutionState state)
{

}

bool ExecutorManager::getExecutor(IExecutor::CallBackFunPtr callBackPtr)
{
    mMutex.lock();
    for(int i = 0; i < mList.size(); ++ i)
    {
        if(mList[i]->getExecutionState() == IDLE)
        {
            callBackPtr(mList[i]);
            return true;
        }
    }

    // No executor available for now
    // Put into waiting queue
    mRequestQueue.push(callBackPtr);

    mMutex.unlock();
}




}
