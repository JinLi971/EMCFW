#ifndef EXECUTORMANAGER_HH
#define EXECUTORMANAGER_HH

#include "IExecutor.hh"

#include <vector>
#include <list>
#include <mutex>

namespace Executor
{

class IExecutable;

class ExecutorManager
{
public:
    static ExecutorManager *getInstance();
    ~ExecutorManager();

    void destoryManager();
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
    std::list<IExecutable*> mRequestQueue;
    std::mutex mMutex;
    std::mutex mDispatchMutex;
    static ExecutorManager* instance;

private:
    ExecutorManager();
    void destory();
};

}


#endif // EXECUTORMANAGER_HH
