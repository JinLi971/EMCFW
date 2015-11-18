#ifndef IEXECUTABLE_H
#define IEXECUTABLE_H

class IExecutor;

namespace Executor
{
class IExecutable
{
public:
    virtual void readyExecutor(IExecutor* instance) = 0;
};
}
#endif // IEXECUTABLE_H
