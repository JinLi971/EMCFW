#include "EvenDispatcher.hh"
#include "dataset/control/LoadSpec.hh"
#include "utils/comm/icommconfig.h"

using namespace DataSet::Control;

namespace Node {
namespace Master {
namespace Dispatcher {

EvenDispatcher::EvenDispatcher(const MasterConf &conf,
                               const std::vector<INode *> &slaveList,
                               const INode& masterNode)
    : DispatcherBase(conf, slaveList, masterNode)
{

}

void EvenDispatcher::apply()
{
    // Execute the strategy of dispatching
    // Even Dispatcher will dispatch every slave node the same work batch
    std::vector<int> nodeCluster;

    // Copy all nodes' id to nodeCluster
    // It means, all nodes are in the same cluster
    for (int i = 0; i < mSlaveList.size(); ++ i)
    {
        nodeCluster.push_back(mSlaveList[i]->getTaskId());
    }

    LoadSpec slaveSpec (mConf.dataFileDir,
                        mConf.dataStartIndex,
                        mConf.dataEndIndex,
                        mMasterNode.getTaskId(),
                        nodeCluster);

    for (int i = 0; i < mSlaveList.size(); ++ i)
    {
        INode* slaveAgent = mSlaveList[i];
        slaveAgent->setLoadSpec(slaveSpec);
    }
}

}
}
}
