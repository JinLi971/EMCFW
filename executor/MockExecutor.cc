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

void MockExecutor::setContext(const IContext &context)
{
    mContext = *(dynamic_cast<const MockContext *>(&context));
}

IResult *MockExecutor::getResult()
{
    return &mResult;
}

void MockExecutor::setResult(MockResult result)
{
    mResult = result;
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
