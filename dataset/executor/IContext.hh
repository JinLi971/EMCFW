#ifndef ICONTEXT_HH
#define ICONTEXT_HH

#define __cplusplus 201103L

#include "ExecutorType.hh"
#include "utils/serializer/ISerializable.hh"
#include <memory>

namespace DataSet
{
namespace Executor
{

class IContext : public ISerializable
{
public:
    typedef std::shared_ptr<DataSet::Executor::IContext> ContextPtr;
    virtual ~IContext() {}

    virtual ContextType getType() = 0;

    // ISerializable interface
public:
    virtual void serialize() = 0;
    virtual void deserialize() = 0;
    virtual GlobalClassId::ClassId getClassId() = 0;
};

}
}
#endif // ICONTEXT_HH
