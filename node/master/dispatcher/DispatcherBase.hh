#ifndef DISPATCHERBASE_HH
#define DISPATCHERBASE_HH

#include "node/master/MasterConf.hh"
#include <vector>
#include "node/INode.hh"
#include "utils/comm/mpiconnection.h"
#include "Dispatcher.hh"

namespace Node {
namespace Master {
namespace Dispatcher {

class DispatcherBase : public IDispatcher
{
public:
    DispatcherBase(const MasterConf& conf,
                   const std::vector<INode *>& slaveList,
                   const INode& masterNode);

    /**
     * @brief apply Apply the strategy of dispatcher
     */
    virtual void apply() = 0;

protected:
    const std::vector<INode *>& mSlaveList;
    const MasterConf& mConf;
    const INode& mMasterNode;

    MpiConnection mCommunicator;
};

}
}
}

#endif // DISPATCHERBASE_HH
