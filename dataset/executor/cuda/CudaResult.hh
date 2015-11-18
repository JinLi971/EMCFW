#ifndef CUDARESULT_HH
#define CUDARESULT_HH

#include "dataset/executor/IResult.hh"

namespace DataSet
{
namespace Executor
{
namespace Cuda
{

class CudaResult : public IResult
{
public:
    CudaResult();

    // IResult interface
public:
    virtual ResultType getType();
};


}
}
}
#endif // CUDARESULT_HH
