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
    virtual ~MockContext() {}
    // IContext interface
public:
    virtual ContextType getType() const;
    virtual void setTestData(const std::string& testString);
    virtual const std::string &getTestData() const;

    // ISerializable interface
public:
    virtual void serialize();
    virtual void deserialize();
    virtual GlobalClassId::ClassId getClassId();

private:
    std::string mTestString;
};

class MockResult : public IResult
{
public:
    MockResult();
    virtual ~MockResult() {}

    // IResult interface
public:
    virtual ResultType getType() const;
    virtual void setTestData(const std::string& testString);
    virtual const std::string &getTestData() const;

    // ISerializable interface
public:
    virtual void serialize();
    virtual void deserialize();
    virtual GlobalClassId::ClassId getClassId();

private:
    std::string mTestString;
};

}
}


#endif // MOCKCONTEXTANDRESULT_HH
