#ifndef EXECUTORFACTORY_HH
#define EXECUTORFACTORY_HH

class IExecutor;

namespace Executor
{

enum ExecutorType
{
    NONE = -1,
    CUDA = 0
};

class ExecutorFactory
{
public:
    ExecutorFactory();

    static IExecutor *getExecutor(ExecutorType type);
};

}


#endif // EXECUTORFACTORY_HH
