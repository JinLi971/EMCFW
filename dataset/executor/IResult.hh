#ifndef IRESULT_H
#define IRESULT_H

#include "ExecutorType.hh"
#include <memory>

namespace DataSet
{
namespace Executor
{

class IResult
{
public:
    typedef std::shared_ptr<DataSet::Executor::IResult> ResultPtr;
    virtual ~IResult() {}

    virtual ResultType getType() = 0;
};

}
}

#endif // IRESULT_H
