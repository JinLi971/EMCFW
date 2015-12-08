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

    // ISerializable interface
public:
    virtual void serialize();
    virtual void deserialize();
    virtual GlobalClassId::ClassId getClassId();
};

}
}
}


#endif // CUDACONTEXT_HH
