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

class CudaExecutor : public IExecutor
{
public:
    CudaExecutor();

    // IExecutor interface
public:
    virtual bool init();
    virtual void start();
    virtual void stop();
    virtual void setContext(const IContext::ContextPtr &context);
    virtual IResult::ResultPtr getResult();
    virtual ExecutorType getType();
    virtual void setResult(IResult::ResultPtr &result);
    virtual void resetToIdle();
};

}
}


#endif // CUDAEXECUTOR_HH
