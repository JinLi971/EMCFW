#ifndef IEXECUTABLE_H
#define IEXECUTABLE_H

class IExecutor;

namespace Executor
{
class IExecutable
{
public:
    void readyExecutor(IExecutor* instance);
};
}
#endif // IEXECUTABLE_H
