#ifndef CUDAEXECUTOR_HH
#define CUDAEXECUTOR_HH

#include "executor/IExecutor.hh"
#include "dataset/executor/cuda/CudaContext.hh"
#include "dataset/executor/cuda/CudaResult.hh"

using namespace DataSet::Executor::Cuda;

namespace Executor
{
namespace Cuda
{

class CudaExecutor : public IExecutor<CudaContext, CudaResult>
{
public:
    CudaExecutor();

    // IExecutor interface
public:
    virtual bool init();
    virtual bool start();
    virtual void abort();
    virtual void setContext(const CudaContext &context);
    virtual CudaResult getResult();
};

}
}


#endif // CUDAEXECUTOR_HH
