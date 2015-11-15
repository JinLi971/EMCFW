#ifndef EXECUTORMANAGER_HH
#define EXECUTORMANAGER_HH

#include "IExecutor.hh"
#include <vector>

namespace Executor
{

class ExecutorManager
{
public:
    ExecutorManager();
    void destory();

    void addExecutor(IExecutor *instance);

private:
    std::vector<IExecutor *> mList;
};

}


#endif // EXECUTORMANAGER_HH
