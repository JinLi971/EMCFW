#ifndef CONTEXTANDRESULTFACTORY_HH
#define CONTEXTANDRESULTFACTORY_HH

#include "IContext.hh"
#include "IResult.hh"

namespace DataSet
{
namespace Executor
{

class ContextAndResultFactory
{

public:
    enum ContextType
    {
        MOCK_CONTEXT = 0,
        CUDA_CONTEXT
    };

    enum ResultType
    {
        MOCK_RESULT = 0,
        CUDA_RESULT
    };

    static IContext::ContextPtr getContext(ContextType type);
    static IResult::ResultPtr getResult(ResultType type);

private:
    ContextAndResultFactory();
};

}
}

#endif // CONTEXTANDRESULTFACTORY_HH
