#ifndef NODEINSTRUCTIONDATA_HH
#define NODEINSTRUCTIONDATA_HH

#include "utils/serializer/ISerializable.hh"
#include "dataset/executor/IContext.hh"
#include "dataset/executor/IResult.hh"

namespace DataSet
{
namespace Control
{

class NodeInstructionData : public ISerializable
{
public:
    NodeInstructionData();

    // ISerializable interface
public:
    virtual void serialize();
    virtual void deserialize();
    virtual GlobalClassId::ClassId getClassId();

private:
    Executor::IContext::ContextPtr mContext;
    Executor::IResult::ResultPtr mResult;
};

}
}


#endif // NODEINSTRUCTIONDATA_HH
