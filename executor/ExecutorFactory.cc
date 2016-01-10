#include "ExecutorFactory.hh"
#include "IExecutor.hh"
#include "executor/cuda/CudaExecutor.hh"
#include "executor/MockExecutor.hh"

namespace Executor
{

ExecutorFactory::ExecutorFactory()
{
}


IExecutor *ExecutorFactory::getExecutor(DataSet::Executor::ExecutorType type)
{
    switch(type)
    {
        case CUDA:
        {
            return new Cuda::CudaExecutor();
        }
        case MOCK:
        {
            return new Mock::MockExecutor();
        }
        default:
            return 0;
    }
}

}
