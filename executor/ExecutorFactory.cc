#include "ExecutorFactory.hh"
#include "IExecutor.hh"
#include "executor/cuda/CudaExecutor.hh"

namespace Executor
{

ExecutorFactory::ExecutorFactory()
{
}


IExecutor *ExecutorFactory::getExecutor(Executor::ExecutorType type)
{
    switch(type)
    {
        case CUDA:
        {
            return new Cuda::CudaExecutor();
        }
        default:
            return NULL;
    }
}

}
