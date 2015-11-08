#ifndef SLAVENODE_HH
#define SLAVENODE_HH

#include "node/INode.hh"
#include "utils/comm/mpiconnection.h"

namespace Node
{
namespace Slave
{

class SlaveNode : public INode
{
public:
    SlaveNode(int taskId);

    // INode interface
public:
    virtual int getTaskId() const;
    virtual void setTaskId(int value);
    virtual const DataSet::Control::LoadSpec &getLoadSpec();
    virtual void setLoadSpec(const DataSet::Control::LoadSpec &loadSpec);
    virtual void dispatchJob();
    virtual void init();
    virtual void loadData();

protected:
    int mTaskId;
    DataSet::Control::LoadSpec mLoadSpec;

    MpiConnection mConnection;
};

}
}


#endif // SLAVENODE_HH