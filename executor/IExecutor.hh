#ifndef IEXECUTOR_HH
#define IEXECUTOR_HH

#include "dataset/executor/IContext.hh"
#include "dataset/executor/IResult.hh"

namespace Executor
{
    enum ExecutionState
    {
        IDLE = -1,
        RESERVED = 0,
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
    typedef std::shared_ptr<IExecutor> IExecutorPtr;
    virtual ~IExecutor() {}

public:
    virtual void resetToIdle() = 0;

    virtual bool init() = 0;
    virtual void start() = 0;
    virtual Executor::ExecutionState getExecutionState() {
        return mExecState;
    }

    virtual void stop() = 0;

    // Ideally the executor should do a deep copy of the Context object
    // So that, the Context will be isolated with executor itself,
    // NO influence to other running executor lauched by SlaveNode
    virtual void setContext(const IContext::ContextPtr& context) = 0;
    // Ideally the executor should do a deep copy of the Result object
    // So that, the Result will be isolated with executor itself,
    // NO influence to other running executor lauched by SlaveNode
    virtual void setResult(IResult::ResultPtr& result) = 0;
    virtual IResult::ResultPtr getResult() = 0;

    virtual void reserve() {
        mExecState = Executor::RESERVED;
    }

    virtual ExecutorType getType() = 0;

    void setId(int id) { mId = id; }

    int getId() const { return mId; }

protected:
    Executor::ExecutionState mExecState;
    unsigned int mId;
};

#endif // IEXECUTOR_HH
