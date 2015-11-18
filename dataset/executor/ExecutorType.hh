#ifndef EXECUTORTYPE_HH
#define EXECUTORTYPE_HH

namespace DataSet
{
namespace Executor
{

enum ExecutorType
{
    NONE = -1,
    MOCK = 0,
    CUDA
};

enum ContextType
{
    NO_CONTEXT = -1,
    MOCK_CONTEXT = 0,
    CUDA_CONTEXT
};

enum ResultType
{
    NO_RESULT = -1,
    MOCK_RESULT = 0,
    CUDA_RESULT
};

}
}
#endif // EXECUTORTYPE_HH
