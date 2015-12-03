#ifndef IEXECUTOR_HH
#define IEXECUTOR_HH

#include "dataset/executor/IContext.hh"
#include "dataset/executor/IResult.hh"

namespace Executor
{
    enum ExecutionState
    {
        IDLE = -1,
        WAITING = 0,
        RUNNING,
        ERROR,
        STOPPED
    };
}

using namespace DataSet::Executor;

class IExecutor
{
public:
    virtual ~IExecutor() {}
    typedef void (* NotifyState)(Executor::ExecutionState,
                                 IExecutor*,
                                 void*);

public:
    virtual void resetToIdle() {
        mExecState = Executor::IDLE;
    }

    virtual bool init() = 0;
    virtual bool start() = 0;
    virtual Executor::ExecutionState getExecutionState() {
        return mExecState;
    }

    virtual void abort() = 0;

    virtual void setContext(const IContext::ContextPtr& context) = 0;
    virtual void setResult(IResult::ResultPtr& result) = 0;
    virtual IResult::ResultPtr getResult() = 0;

    virtual void setNotifyHandler(NotifyState funPtr, void* handler) {
        mStateHandler = handler;
        mStateFunPtr = funPtr;
    }

    virtual NotifyState getNotifyHanlder(void* handler) {
        handler = mStateHandler;
        return mStateFunPtr;
    }

    virtual ExecutorType getType() = 0;

protected:
    virtual void fireStateChange() {
        (*mStateFunPtr)(mExecState, this, mStateHandler);
    }

protected:
    Executor::ExecutionState mExecState;
    NotifyState mStateFunPtr;
    void* mStateHandler;
};

#endif // IEXECUTOR_HH
