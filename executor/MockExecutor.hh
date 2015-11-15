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
    virtual bool start();
    virtual void abort();
    virtual void setContext(const MockContext &context);
    virtual IResult getResult();

public:
    void setState(ExecutionState state);
    void setReturnVal(bool value);
    void setResult(MockResult result);

private:
    bool mReturnVal;
    MockContext mContext;
    MockResult mResult;
};

}
}

#endif // MOCKEXECUTOR_HH
