#include "MockContextAndResult.hh"
#include "ExecutorType.hh"
#include <cassert>

namespace DataSet
{
namespace Executor
{

MockContext::MockContext()
{

}

ContextType MockContext::getType() const
{
    return MOCK_CONTEXT;
}

void MockContext::setTestData(const std::string &testString)
{
    mTestString = testString;
}

const std::string &MockContext::getTestData() const
{
    return mTestString;
}

void MockContext::serialize()
{
    mSerializer.clearContent();
    mSerializer << GlobalClassId::MOCK_CONTEXT;
    mSerializer << mTestString;
}

void MockContext::deserialize()
{
    mSerializer >> mClassId;
    assert(mClassId == GlobalClassId::MOCK_CONTEXT);

    mSerializer >> mTestString;

    assert(mSerializer.getTotalLength() == 0);
}

GlobalClassId::ClassId MockContext::getClassId()
{
    return GlobalClassId::MOCK_CONTEXT;
}

MockResult::MockResult()
{

}

ResultType MockResult::getType() const
{
    return MOCK_RESULT;
}

void MockResult::setTestData(const std::string &testString)
{
    mTestString = testString;
}

const std::string &MockResult::getTestData() const
{
    return mTestString;
}

void MockResult::serialize()
{
    mSerializer.clearContent();
    mSerializer << GlobalClassId::MOCK_RESULT;
    mSerializer << mTestString;
}

void MockResult::deserialize()
{
    mSerializer >> mClassId;
    assert(mClassId == GlobalClassId::MOCK_RESULT);

    mSerializer >> mTestString;

    assert(mSerializer.getTotalLength() == 0);
}

GlobalClassId::ClassId MockResult::getClassId()
{
    return GlobalClassId::MOCK_RESULT;
}



}
}
