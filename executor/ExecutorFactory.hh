#ifndef EXECUTORFACTORY_HH
#define EXECUTORFACTORY_HH

#include "dataset/executor/ExecutorType.hh"

class IExecutor;

namespace Executor
{

class ExecutorFactory
{
public:
    ExecutorFactory();

    static IExecutor *getExecutor(DataSet::Executor::ExecutorType type);
};

}


#endif // EXECUTORFACTORY_HH
