#ifndef DISPATCHERFACTORY_H
#define DISPATCHERFACTORY_H

#include "EvenDispatcher.hh"
#include "Dispatcher.hh"

namespace Node {
namespace Master {
namespace Dispatcher {


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
#endif // DISPATCHERFACTORY_H
