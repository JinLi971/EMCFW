#ifndef NODEINSTRUCTIONDATA_HH
#define NODEINSTRUCTIONDATA_HH

#include "utils/serializer/ISerializable.hh"
#include "dataset/executor/IContext.hh"
#include "dataset/executor/IResult.hh"
#include "dataset/executor/ContextAndResultFactory.hh"
#include "node/INode.hh"

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
    virtual Executor::ContextType getContextType();
    virtual void setContextType(const Executor::ContextType type);
    virtual Executor::IContext::ContextPtr &getContextPtr();
    virtual Executor::ResultType getResultType();
    virtual void setResultType(const Executor::ResultType type);
    virtual Executor::IResult::ResultPtr &getResultPtr();

    virtual unsigned int getInstruction();
    virtual void setInstruction(const unsigned int cmd);

    unsigned int getReportColor() const;
    void setReportColor(unsigned int value);

private:
    Executor::IContext::ContextPtr mContext;
    Executor::IResult::ResultPtr mResult;

    Executor::ContextType mContextType;
    Executor::ResultType mResultType;

    unsigned int mInstruction;
    unsigned int mReportColor;
};

}
}


#endif // NODEINSTRUCTIONDATA_HH
