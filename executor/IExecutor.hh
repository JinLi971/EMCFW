#ifndef IEXECUTOR_HH
#define IEXECUTOR_HH

#include "dataset/executor/IContext.hh"
#include "dataset/executor/IResult.hh"

namespace Executor
{
    enum ExecutionState
    {
        IDLE = -1,
        INIT = 0,
        WAITING,
        RUNNING,
        ERROR,
        STOPPED
    };
}

using namespace DataSet::Executor;

class IExecutor
{
public:
    typedef void (* CallBackFunPtr)(IExecutor*);
    typedef void (* NotifyState)(Executor::ExecutionState);

public:
    virtual bool init() = 0;
    virtual bool start() = 0;
    virtual Executor::ExecutionState getExecutionState() {
        return mExecState;
    }

    virtual void abort() = 0;

    virtual void setContext(const IContext& context) = 0;
    virtual IResult getResult() = 0;

    virtual void setNotifyHandler(NotifyState handler) {
        mStateHandler = handler;
    }

    virtual NotifyState getNotifyHanlder() {
        return mStateHandler;
    }

protected:
    virtual void fireStateChange() {
        (*mStateHandler)(mExecState);
    }

protected:
    Executor::ExecutionState mExecState;
    NotifyState mStateHandler;
};

#endif // IEXECUTOR_HH
