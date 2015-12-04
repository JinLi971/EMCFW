#include "ContextAndResultFactory.hh"
#include "MockContextAndResult.hh"
#include "cuda/CudaContext.hh"


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

}

}
}
