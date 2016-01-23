#include "NodeInstructionData.hh"
#include "dataset/executor/ContextAndResultFactory.hh"
#include <cassert>

namespace DataSet
{
namespace Control
{


NodeInstructionData::NodeInstructionData()
{

}

void NodeInstructionData::serialize()
{
    mSerializer.clearContent();
    mSerializer << GlobalClassId::NODE_INSTRUCTION;
    mSerializer << mInstruction;
    mSerializer << mContextType;

    if(mContextType != Executor::NO_CONTEXT)
    {
        mContext->serialize();
        mSerializer << mContext->getSerializer();
    }

    mSerializer << mResultType;

    if(mResultType != Executor::NO_RESULT)
    {
        mResult->serialize();
        mSerializer << mResult->getSerializer();
    }

    mSerializer << mReportColor;
}

void NodeInstructionData::deserialize()
{
    int classId;
    mSerializer >> classId;

    assert(((GlobalClassId::ClassId) classId) == GlobalClassId::NODE_INSTRUCTION);

    mSerializer >> mInstruction;
    mSerializer >> mContextType;

    if(mContextType == DataSet::Executor::NO_CONTEXT)
    {
        mContext.reset();
    } else {
        mContext = DataSet::Executor::ContextAndResultFactory::getContext(mContextType);
        assert(mContext.get());

        mSerializer >> mContext->getSerializerRef();
        mContext->deserialize();
    }

    mSerializer >> mResultType;

    if(mResultType == DataSet::Executor::NO_RESULT)
    {
        mResult.reset();
    } else {
        mResult = Executor::ContextAndResultFactory::getResult(mResultType);
        assert(mResult.get());

        mSerializer >> mResult->getSerializerRef();
        mResult->deserialize();
    }

    mSerializer >> mReportColor;

    assert(mSerializer.getTotalLength() == 0);
}

GlobalClassId::ClassId NodeInstructionData::getClassId()
{
    return GlobalClassId::NODE_INSTRUCTION;
}

Executor::ContextType NodeInstructionData::getContextType()
{
    return mContextType;
}

void NodeInstructionData::setContextType(const Executor::ContextType type)
{
    mContextType = type;
    mContext = DataSet::Executor::ContextAndResultFactory::getContext(type);
}

Executor::IContext::ContextPtr &NodeInstructionData::getContextPtr()
{
    return mContext;
}

Executor::ResultType NodeInstructionData::getResultType()
{
    return mResultType;
}

void NodeInstructionData::setResultType(const Executor::ResultType type)
{
    mResultType = type;
    mResult = DataSet::Executor::ContextAndResultFactory::getResult(type);
}

Executor::IResult::ResultPtr &NodeInstructionData::getResultPtr()
{
    return mResult;
}

unsigned int NodeInstructionData::getInstruction()
{
    return mInstruction;
}

void NodeInstructionData::setInstruction(const unsigned int cmd)
{
    mInstruction = cmd;
}
unsigned int NodeInstructionData::getReportColor() const
{
    return mReportColor;
}

void NodeInstructionData::setReportColor(unsigned int value)
{
    mReportColor = value;
}

}
}
