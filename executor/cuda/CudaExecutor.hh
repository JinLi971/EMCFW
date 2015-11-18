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
    virtual bool start();
    virtual void abort();
    virtual void setContext(const IContext &context);
    virtual IResult* getResult();
    virtual ExecutorType getType();

    // IExecutor interface
};

}
}


#endif // CUDAEXECUTOR_HH
