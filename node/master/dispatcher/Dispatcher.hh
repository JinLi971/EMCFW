#ifndef DISPATCHER_HH
#define DISPATCHER_HH

#include "EvenDispatcher.hh"

namespace Node {
namespace Master {
namespace Dispatcher {

class IDispatcher
{
public:
    virtual ~IDispatcher() {}

    virtual void apply() = 0;
};

class DispatcherFactory
{
public:
    enum DispatcherType
    {
        INVALID = -1,
        EVEN = 0
    };

    static IDispatcher* getDispatcher(DispatcherType type,
                                     const MasterConf& conf,
                                     const std::vector<INode *>& slaveList,
                                     const INode& masterNode)
    {
        switch(type)
        {
            case EVEN:
            {
                return new EvenDispatcher(conf, slaveList, masterNode);
            }
            default:
                return NULL;
        }
    }
};

}
}
}

#endif // DISPATCHER_HH
