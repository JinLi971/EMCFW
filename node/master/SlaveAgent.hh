#ifndef SLAVEAGENT_HH
#define SLAVEAGENT_HH

#include "utils/comm/mpiconnection.h"
#include "node/INode.hh"
#include "dataset/control/LoadSpec.hh"

namespace Node {
namespace Master {

class SlaveAgent : public INode
{
public:
    SlaveAgent(const int taskId);

protected:
    MpiConnection mCommunicator;

    // INode interface
public:
    virtual int getTaskId() const { return mTaskId; }
    virtual void setTaskId(int value) { mTaskId = value; }
    virtual const DataSet::Control::LoadSpec &getLoadSpec() { return mLoadSpec; }
    virtual void setLoadSpec(const DataSet::Control::LoadSpec &loadSpec);
    virtual void init();
    virtual void dispatchJob();
    virtual void loadData();
    virtual void start();
    virtual void stop(int taskId);
    virtual bool destory();

protected:
    int mTaskId;
    DataSet::Control::LoadSpec mLoadSpec;

private:
    void constructGroup();
};

}
}


#endif // SLAVEAGENT_HH
