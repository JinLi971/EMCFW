#ifndef SLAVEAGENT_HH
#define SLAVEAGENT_HH

#include "utils/comm/mpiconnection.h"
#include "node/INode.hh"

namespace Node {
namespace Master {

class SlaveAgent : public INode
{
public:
    SlaveAgent(const int taskId);

private:
    SlaveAgent() {}
    MpiConnection mCommunicator;

    // INode interface
public:
    int getTaskId() { return mTaskId; }
    void setTaskId(int value) { mTaskId = value; }
    const DataSet::Control::LoadSpec &getLoadSpec() { return mLoadSpec; }
    void setLoadSpec(const DataSet::Control::LoadSpec &loadSpec);
    void init();
    void dispatchJob();
    void loadData();

private:
    int mTaskId;
    DataSet::Control::LoadSpec mLoadSpec;
};

}
}


#endif // SLAVEAGENT_HH
