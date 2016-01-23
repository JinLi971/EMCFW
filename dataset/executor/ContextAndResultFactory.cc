#include "ContextAndResultFactory.hh"
#include "MockContextAndResult.hh"
#include "cuda/CudaContext.hh"
#include "cuda/CudaResult.hh"


namespace DataSet
{
namespace Executor
{

ContextAndResultFactory::ContextAndResultFactory()
{
}


IContext::ContextPtr ContextAndResultFactory::getContext(ContextType type)
{
    switch(type)
    {
        case MOCK_CONTEXT:
        {
            return std::make_shared<MockContext>();
        }
        case CUDA_CONTEXT:
        {
            return std::make_shared<Cuda::CudaContext>();
        }
        default:
            return IContext::ContextPtr(NULL);
    }
}

IResult::ResultPtr ContextAndResultFactory::getResult(ResultType type)
{
    switch(type)
    {
        case MOCK_RESULT:
        {
            return std::make_shared<MockResult>();
        }
        case CUDA_RESULT:
        {
            return std::make_shared<Cuda::CudaResult>();
        }
        default:
            return IResult::ResultPtr(NULL);
    }
}

}
}
