#ifndef MOCKEXECUTOR_HH
#define MOCKEXECUTOR_HH


#include "executor/IExecutor.hh"
#include "dataset/executor/MockContextAndResult.hh"

using namespace DataSet::Executor;

namespace Executor
{
namespace Mock
{

class MockExecutor : public IExecutor
{
public:
    MockExecutor();

    // IExecutor interface
public:
    virtual bool init();
    virtual void start();
    virtual void abort();
    virtual void setContext(const IContext::ContextPtr &context);
    virtual IResult::ResultPtr getResult();
    virtual void setResult(IResult::ResultPtr &result);
    virtual ExecutorType getType();

public:
    void setState(ExecutionState state);
    void setReturnVal(bool value);


private:
    bool mReturnVal;
    MockContext mContext;
    MockResult mResult;
};

}
}

#endif // MOCKEXECUTOR_HH
