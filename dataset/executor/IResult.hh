#ifndef IRESULT_H
#define IRESULT_H

#include "ExecutorType.hh"
#include "utils/serializer/ISerializable.hh"
#include <memory>

namespace DataSet
{
namespace Executor
{

class IResult : public ISerializable
{
public:
    typedef std::shared_ptr<DataSet::Executor::IResult> ResultPtr;
    virtual ~IResult() {}

    virtual ResultType getType() = 0;

    // ISerializable interface
public:
    virtual void serialize() = 0;
    virtual void deserialize() = 0;
    virtual GlobalClassId::ClassId getClassId() = 0;
};

}
}

#endif // IRESULT_H
