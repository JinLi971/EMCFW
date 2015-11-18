#ifndef CUDACONTEXT_HH
#define CUDACONTEXT_HH

#include "dataset/executor/IContext.hh"

namespace DataSet
{
namespace Executor
{
namespace Cuda
{

class CudaContext : public IContext
{
public:
    CudaContext();

    // IContext interface
public:
    virtual ContextType getType();
};

}
}
}


#endif // CUDACONTEXT_HH
