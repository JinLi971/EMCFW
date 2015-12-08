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
            return IContext::ContextPtr(new MockContext());
        }
        case CUDA_CONTEXT:
        {
            return IContext::ContextPtr(new Cuda::CudaContext());
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
            return IResult::ResultPtr(new MockResult());
        }
        case CUDA_RESULT:
        {
            return IResult::ResultPtr(new Cuda::CudaResult());
        }
        default:
            return IResult::ResultPtr(NULL);
    }
}

}
}
