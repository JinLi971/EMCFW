#ifndef CONTEXTANDRESULTFACTORY_HH
#define CONTEXTANDRESULTFACTORY_HH

#include "IContext.hh"
#include "IResult.hh"
#include "ExecutorType.hh"

namespace DataSet
{
namespace Executor
{

class ContextAndResultFactory
{

public:
    static IContext::ContextPtr getContext(ContextType type);
    static IResult::ResultPtr getResult(ResultType type);

private:
    ContextAndResultFactory();
};

}
}

#endif // CONTEXTANDRESULTFACTORY_HH
