#ifndef IEXECUTABLE_H
#define IEXECUTABLE_H

#include "dataset/executor/ExecutorType.hh"
#include "IExecutor.hh"

namespace Executor
{
class IExecutable
{
public:
    virtual bool readyExecutor(IExecutor::IExecutorPtr &instance) = 0;
    virtual DataSet::Executor::ExecutorType getRequiredExecutorType() = 0;
};
}
#endif // IEXECUTABLE_H
