#ifndef DISPATCHER_HH
#define DISPATCHER_HH

namespace Node {
namespace Master {
namespace Dispatcher {

class IDispatcher
{
public:
    virtual ~IDispatcher() {}

    virtual void apply() = 0;
};

}
}
}

#endif // DISPATCHER_HH
