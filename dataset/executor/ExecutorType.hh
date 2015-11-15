#ifndef EXECUTORTYPE_HH
#define EXECUTORTYPE_HH

namespace DataSet
{
namespace Executor
{

enum ExecutorType
{
    NONE = -1,
    CUDA = 0
};

enum ContextType
{
    NO_CONTEXT = -1,
    CUDA_CONTEXT = 0
};

enum ResultType
{
    NO_RESULT = -1,
    CUDA_RESULT = 0
};

}
}
#endif // EXECUTORTYPE_HH
