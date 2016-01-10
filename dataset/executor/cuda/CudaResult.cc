#include "CudaResult.hh"


namespace DataSet
{
namespace Executor
{
namespace Cuda
{


CudaResult::CudaResult()
{
}

ResultType CudaResult::getType() const
{
    return CUDA_RESULT;
}

void CudaResult::serialize()
{

}

void CudaResult::deserialize()
{

}

GlobalClassId::ClassId CudaResult::getClassId()
{
    return GlobalClassId::CUDA_RESULT;
}

}
}
}
