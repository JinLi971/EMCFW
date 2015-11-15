#ifndef MOCKCONTEXTANDRESULT_HH
#define MOCKCONTEXTANDRESULT_HH

#include "dataset/executor/IResult.hh"
#include "dataset/executor/IContext.hh"

namespace DataSet
{
namespace Executor
{

class MockContext : public IContext
{
public:
    MockContext();
};

class MockResult : public IResult
{
public:
    MockResult();
};

}
}


#endif // MOCKCONTEXTANDRESULT_HH
