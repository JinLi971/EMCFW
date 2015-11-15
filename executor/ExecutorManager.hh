#ifndef EXECUTORMANAGER_HH
#define EXECUTORMANAGER_HH

#include "IExecutor.hh"

#include <vector>
#include <queue>
#include <mutex>

namespace Executor
{

class IExecutable;

class ExecutorManager
{
public:
    ExecutorManager();
    void destory();
    void addExecutor(IExecutor *instance);
    bool getExecutor(IExecutable* callBackInstance);

public:
    static void handleExecutorStateChange(ExecutionState state,
                                          IExecutor *instance,
                                          void* handler);

protected:
    void dispatchJob(IExecutor *instance);

private:
    std::vector<IExecutor*> mList;
    std::queue<IExecutable*> mRequestQueue;
    std::mutex mMutex;
    std::mutex mDispatchMutex;
};

}


#endif // EXECUTORMANAGER_HH
