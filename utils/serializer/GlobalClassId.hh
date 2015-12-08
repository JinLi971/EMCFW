#ifndef GLOBALCLASSID_HH
#define GLOBALCLASSID_HH

class GlobalClassId
{
public:
    enum ClassId {
        INVALID = 1,
        MASTER_CONF = 0,
        LOAD_SPEC,
        NODE_INSTRUCTION,
        MOCK_CONTEXT,
        MOCK_RESULT,
        CUDA_CONTEXT,
        CUDA_RESULT
    };
};

#endif // GLOBALCLASSID_HH
