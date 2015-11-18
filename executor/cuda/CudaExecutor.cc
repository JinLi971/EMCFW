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

bool CudaExecutor::start()
{
    mExecState = RUNNING;
    return true;
}

void CudaExecutor::abort()
{
    mExecState = STOPPED;
}

void CudaExecutor::setContext(const IContext &context)
{

}

IResult *CudaExecutor::getResult()
{

}

ExecutorType CudaExecutor::getType()
{
    return CUDA;
}



}
}
