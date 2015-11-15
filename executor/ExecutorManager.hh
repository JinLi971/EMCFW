#ifndef EXECUTORMANAGER_HH
#define EXECUTORMANAGER_HH

#include "IExecutor.hh"
#include <vector>
#include <queue>
#include <mutex>

namespace Executor
{

class ExecutorManager
{
public:
    ExecutorManager();
    void destory();
    void addExecutor(IExecutor *instance);
    bool getExecutor(IExecutor::CallBackFunPtr callBackPtr);

protected:
    static void handleExecutorStateChange(ExecutionState state);

private:
    std::vector<IExecutor*> mList;
    std::queue<IExecutor::CallBackFunPtr> mRequestQueue;
    std::mutex mMutex;
};

}


#endif // EXECUTORMANAGER_HH
