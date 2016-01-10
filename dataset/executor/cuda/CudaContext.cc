#include "CudaContext.hh"
#include "utils/serializer/GlobalClassId.hh"

namespace DataSet
{
namespace Executor
{
namespace Cuda
{

CudaContext::CudaContext()
{
}

ContextType CudaContext::getType() const
{
    return CUDA_CONTEXT;
}

void CudaContext::serialize()
{

}

void CudaContext::deserialize()
{

}

GlobalClassId::ClassId CudaContext::getClassId()
{
    return GlobalClassId::CUDA_CONTEXT;
}


}
}
}
