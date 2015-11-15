#ifndef ICONTEXT_HH
#define ICONTEXT_HH

#include "ExecutorType.hh"

namespace DataSet
{
namespace Executor
{

class IContext
{
public:
    virtual ~IContext() {}

    virtual ContextType getType() = 0;
};

}
}
#endif // ICONTEXT_HH
