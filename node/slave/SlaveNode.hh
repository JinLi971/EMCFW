#ifndef SLAVENODE_HH
#define SLAVENODE_HH

#include "node/INode.hh"
#include "utils/comm/mpiconnection.h"
#include "executor/ExecutorManager.hh"
#include "executor/IExecutable.hh"

#include "dataset/executor/IContext.hh"
#include "dataset/executor/IResult.hh"
#include "dataset/control/NodeInstructionData.hh"

#include <memory>

namespace Node
{
namespace Slave
{

class SlaveNode : public INode, Executor::IExecutable
{
public:
    SlaveNode(int taskId);
    virtual ~SlaveNode();

    // INode interface
public:
    virtual int getTaskId() const;
    virtual void setTaskId(int value);
    virtual const DataSet::Control::LoadSpec &getLoadSpec() const;
    virtual void setLoadSpec(const DataSet::Control::LoadSpec &loadSpec);
    virtual void dispatchJob();
    virtual void init();
    virtual void loadData();
    virtual void start();
    virtual void stop(int taskId);
    virtual bool destory();

public:
    virtual void setContext(DataSet::Executor::IContext *ctx);
    virtual const IContext::ContextPtr &getContext() const;
    virtual IContext::ContextPtr &getContextRef();

    virtual void setResult(IResult *result);
    virtual const IResult::ResultPtr &getResult() const;
    virtual IResult::ResultPtr &getResultRef();

protected:
    int mTaskId;
    DataSet::Control::LoadSpec mLoadSpec;
    MpiConnection mConnection;
    DataSet::Executor::IContext::ContextPtr mContext;
    DataSet::Executor::IResult::ResultPtr mResult;
    IExecutor::IExecutorPtr mExecutor;
    DataSet::Control::NodeInstructionData mCmd;
    int mControlId;
    MPI_Comm mMpiWorldComm;


    // IExecutable interface
public:
    virtual bool readyExecutor(IExecutor::IExecutorPtr &instance);
    virtual ExecutorType getRequiredExecutorType();

    int getControlId() const;
    void setControlId(int value);

private:
    void prepareExecutor();
    void reportResultToClusterHead();
    void startJob();
    void cleanResource();


};

}
}


#endif // SLAVENODE_HH
