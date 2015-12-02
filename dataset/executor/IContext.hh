#ifndef ICONTEXT_HH
#define ICONTEXT_HH

#define __cplusplus 201103L

#include "ExecutorType.hh"
#include <memory>

namespace DataSet
{
namespace Executor
{

class IContext
{
public:
    typedef std::shared_ptr<DataSet::Executor::IContext> ContextPtr;
    virtual ~IContext() {}

    virtual ContextType getType() = 0;
};

}
}
#endif // ICONTEXT_HH
