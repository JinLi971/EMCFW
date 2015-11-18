#include "MockContextAndResult.hh"
#include "ExecutorType.hh"

namespace DataSet
{
namespace Executor
{

MockContext::MockContext()
{

}

ContextType MockContext::getType()
{
    return MOCK_CONTEXT;
}

MockResult::MockResult()
{

}

ResultType MockResult::getType()
{

    return MOCK_RESULT;
}



}
}
