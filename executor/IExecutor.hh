#ifndef IEXECUTOR_HH
#define IEXECUTOR_HH

template<class ContextType, class ResultType>
class IExecutor
{
public:

    enum ExecutionState
    {
        NONE = -1,
        INIT = 0,
        WAITING,
        RUNNING,
        ERROR,
        STOPPED
    };

public:
    virtual bool init() = 0;
    virtual bool start() = 0;
    virtual ExecutionState getExecutionState() {
        return mExecState;
    }

    virtual void abort() = 0;

    virtual void setContext(const ContextType& context) = 0;
    virtual ResultType getResult() = 0;

protected:
    ExecutionState mExecState;
};

#endif // IEXECUTOR_HH
