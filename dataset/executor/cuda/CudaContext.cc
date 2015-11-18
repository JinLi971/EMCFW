#include "CudaContext.hh"

namespace DataSet
{
namespace Executor
{
namespace Cuda
{

CudaContext::CudaContext()
{
}

ContextType CudaContext::getType()
{
    return CUDA_CONTEXT;
}


}
}
}
