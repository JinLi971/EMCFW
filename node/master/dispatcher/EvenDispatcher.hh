#ifndef EVENDISPATCHER_HH
#define EVENDISPATCHER_HH

#include "DispatcherBase.hh"

namespace Node {
namespace Master {
namespace Dispatcher {

class EvenDispatcher : public DispatcherBase
{
public:
    EvenDispatcher(const MasterConf& conf,
                   const std::vector<INode *>& slaveList,
                   const INode& masterNode);


    virtual void apply();
};

}
}
}


#endif // EVENDISPATCHER_HH
