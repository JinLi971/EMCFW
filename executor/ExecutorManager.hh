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
    void addExecutor(IExecutor::IExecutorPtr &instance);
    bool getExecutor(IExecutable* callBackInstance);
    int getSizeofExecutors(DataSet::Executor::ExecutorType type);

    std::vector<IExecutor::IExecutorPtr>& getExecutorVectorRef() { return mList; }

public:
    void handleExecutorStateChange(ExecutionState state,
                                          int id);


protected:
    void dispatchJob(IExecutor::IExecutorPtr &instance);

private:
    std::vector<IExecutor::IExecutorPtr> mList;
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
