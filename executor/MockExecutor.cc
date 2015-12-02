#include "MockExecutor.hh"
#include <stdio.h>

namespace Executor
{
namespace Mock
{

MockExecutor::MockExecutor()
    : mReturnVal(true)
{
}

bool MockExecutor::init()
{
    printf("Executor in Init\n");
    mExecState = WAITING;
    return mReturnVal;
}

bool MockExecutor::start()
{
    printf("Executor in Start\n");
    mExecState = RUNNING;
    return mReturnVal;
}

void MockExecutor::abort()
{
    printf("Executor aborted!\n");
    mExecState = STOPPED;
}

void MockExecutor::setContext(const IContext::ContextPtr &context)
{
    mContext = *(static_cast<const MockContext *>(context.get()));
}

IResult::ResultPtr MockExecutor::getResult()
{
    return std::make_shared<MockResult>(mResult);
}

ExecutorType MockExecutor::getType()
{
    return MOCK;
}

void MockExecutor::setResult(IResult::ResultPtr &result)
{
    mResult = *(dynamic_cast<MockResult *>(result.get()));
}


void MockExecutor::setState(Executor::ExecutionState state)
{
    mExecState = state;
}

void MockExecutor::setReturnVal(bool value)
{
    mReturnVal = value;
}

}
}
