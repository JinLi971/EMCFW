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
    MasterNode();

    // INode interface
public:
    int getTaskId();
    void setTaskId(int value);
    virtual void init();
    virtual void loadData();
    virtual void dispatchJob();

private:
    void loadMasterConf();

private:
    int mTaskId;
    MasterConf mConf;
    std::vector<INode *> mSlaveList;
};

} //Master NS
} //Node NS


#endif // MASTERNODE_HH
