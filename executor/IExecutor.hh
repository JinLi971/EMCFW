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
    virtual ~IExecutor() {}
    typedef void (* NotifyState)(Executor::ExecutionState,
                                 IExecutor*,
                                 void*);

public:
    virtual void resetToInit() {
        mExecState = Executor::INIT;
    }

    virtual bool init() = 0;
    virtual bool start() = 0;
    virtual Executor::ExecutionState getExecutionState() {
        return mExecState;
    }

    virtual void abort() = 0;

    virtual void setContext(const IContext& context) = 0;
    virtual IResult getResult() = 0;

    virtual void setNotifyHandler(NotifyState funPtr, void* handler) {
        mStateHandler = handler;
        mStateFunPtr = funPtr;
    }

    virtual NotifyState getNotifyHanlder(void* handler) {
        handler = mStateHandler;
        return mStateFunPtr;
    }

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
