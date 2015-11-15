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
            if((*iter)->getExecutionState() == IExecutor::STOPPED)
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
    mList.push_back(instance);
}


}
