#ifndef NODECONSTANTS_HH
#define NODECONSTANTS_HH

namespace Node {

class NodeConstants {

public:
    enum NodeType {
        NODE_NONE = -1,
        MASTER = 0,
        SLAVE,
        SLAVE_AGENT
    };

    enum ProcessorType {
        PROCESSOR_NONE = -1,
        CPU = 0,
        GPU
    };

    enum MemType {
        MEM_NONE = -1,
        CPU_MEM = 0,
        GPU_MEM
    };

};

}

#endif // NODECONSTANTS_HH
