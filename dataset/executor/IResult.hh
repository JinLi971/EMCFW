#ifndef IRESULT_H
#define IRESULT_H

#include "ExecutorType.hh"

namespace DataSet
{
namespace Executor
{

class IResult
{
public:
    virtual ~IResult() {}

    virtual ResultType getType() = 0;
};

}
}

#endif // IRESULT_H
