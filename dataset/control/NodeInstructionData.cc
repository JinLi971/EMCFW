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
    }
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
}

Executor::IResult::ResultPtr &NodeInstructionData::getResultPtr()
{
    return mResult;
}

Node::INode::InstructionState NodeInstructionData::getInstruction()
{
    return mInstruction;
}

void NodeInstructionData::setInstruction(const Node::INode::InstructionState cmd)
{
    mInstruction = cmd;
}



}
}
