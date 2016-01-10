#ifndef EXECUTORMANAGER_HH
#define EXECUTORMANAGER_HH

#include "IExecutor.hh"
#include "dataset/executor/ExecutorType.hh"

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
    int getSizeofExecutors(DataSet::Executor::ExecutorType type);

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
    static std::unique_ptr<ExecutorManager> mInstance;

private:
    ExecutorManager();
    void destory();
};

}


#endif // EXECUTORMANAGER_HH
