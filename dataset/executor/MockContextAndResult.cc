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

void MockContext::serialize()
{
    mSerializer << GlobalClassId::MOCK_CONTEXT;
}

void MockContext::deserialize()
{

}

GlobalClassId::ClassId MockContext::getClassId()
{
    return GlobalClassId::MOCK_CONTEXT;
}

MockResult::MockResult()
{

}

ResultType MockResult::getType()
{
    return MOCK_RESULT;
}

void MockResult::serialize()
{
    mSerializer << GlobalClassId::MOCK_RESULT;
}

void MockResult::deserialize()
{

}

GlobalClassId::ClassId MockResult::getClassId()
{
    return GlobalClassId::MOCK_RESULT;
}



}
}
