#include "CudaExecutor.hh"
#include "executor/ExecutorManager.hh"

namespace Executor
{
namespace Cuda
{


CudaExecutor::CudaExecutor()
{
    mExecState = IDLE;
}

bool CudaExecutor::init()
{
    mExecState = WAITING;
    return true;
}

void CudaExecutor::start()
{
    mExecState = RUNNING;
}

void CudaExecutor::stop()
{
    mExecState = STOPPED;
}

void CudaExecutor::setContext(const IContext::ContextPtr &context)
{

}

IResult::ResultPtr CudaExecutor::getResult()
{

}

ExecutorType CudaExecutor::getType()
{
    return CUDA;
}

void CudaExecutor::setResult(IResult::ResultPtr &result)
{

}

void CudaExecutor::resetToIdle()
{
    mExecState = IDLE;
    Executor::ExecutorManager::getInstance()->handleExecutorStateChange(mExecState, mId);
}



}
}
