#ifndef EXECUTORFACTORY_HH
#define EXECUTORFACTORY_HH

#include "dataset/executor/ExecutorType.hh"
#include "IExecutor.hh"

class IExecutor;

namespace Executor
{

class ExecutorFactory
{
public:
    static IExecutor::IExecutorPtr getExecutor(DataSet::Executor::ExecutorType type);

private:
    ExecutorFactory();
};

}


#endif // EXECUTORFACTORY_HH
