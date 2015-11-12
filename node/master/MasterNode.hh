#ifndef MASTERNODE_HH
#define MASTERNODE_HH

#include "../INode.hh"
#include <vector>
#include "MasterConf.hh"

namespace Node {
namespace Master {

class MasterNode : public INode
{
public:
    MasterNode(int taskId);

    // INode interface
public:
    virtual int getTaskId() const;
    virtual void setTaskId(int value);
    virtual void init();
    virtual void loadData();
    virtual void dispatchJob();
    virtual const DataSet::Control::LoadSpec &getLoadSpec();
    virtual void setLoadSpec(const DataSet::Control::LoadSpec &loadSpec);

private:
    void loadMasterConf();

private:
    int mTaskId;
    MasterConf mConf;
    std::vector<INode *> mSlaveList;
    DataSet::Control::LoadSpec mEmptyLoadSpec;
};

} //Master NS
} //Node NS


#endif // MASTERNODE_HH
