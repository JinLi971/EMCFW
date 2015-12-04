#include "CudaExecutor.hh"

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

void CudaExecutor::abort()
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



}
}
