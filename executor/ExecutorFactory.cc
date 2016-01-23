#include "ExecutorFactory.hh"
#include "executor/cuda/CudaExecutor.hh"
#include "executor/MockExecutor.hh"

namespace Executor
{

ExecutorFactory::ExecutorFactory()
{
}


IExecutor::IExecutorPtr ExecutorFactory::getExecutor(DataSet::Executor::ExecutorType type)
{
    switch(type)
    {
        case CUDA:
        {
            return std::make_shared<Cuda::CudaExecutor>();
        }
        case MOCK:
        {
            return std::make_shared<Mock::MockExecutor>();
        }
        default:
            return IExecutor::IExecutorPtr();
    }
}

}
