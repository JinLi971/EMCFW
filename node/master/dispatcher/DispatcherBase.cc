#include "DispatcherBase.hh"

namespace Node {
namespace Master {
namespace Dispatcher {

DispatcherBase::DispatcherBase(const MasterConf &conf,
                                                  const std::vector<INode *> &slaveList,
                                                  const INode &masterNode)
    : mSlaveList(slaveList),
      mConf(conf),
      mMasterNode(masterNode)
{
}

}
}
}
