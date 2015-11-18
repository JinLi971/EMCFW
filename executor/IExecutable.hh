#ifndef IEXECUTABLE_H
#define IEXECUTABLE_H

#include "dataset/executor/ExecutorType.hh"

class IExecutor;

namespace Executor
{
class IExecutable
{
public:
    virtual bool readyExecutor(IExecutor* instance) = 0;
    virtual DataSet::Executor::ExecutorType getRequiredExecutorType() = 0;
};
}
#endif // IEXECUTABLE_H
