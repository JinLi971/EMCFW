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

ResultType CudaResult::getType()
{
    return CUDA_RESULT;
}

}
}
}
