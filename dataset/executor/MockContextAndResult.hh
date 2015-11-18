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

    // IContext interface
public:
    virtual ContextType getType();
};

class MockResult : public IResult
{
public:
    MockResult();

    // IResult interface
public:
    virtual ResultType getType();
};

}
}


#endif // MOCKCONTEXTANDRESULT_HH
