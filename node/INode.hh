#ifndef INODE_HH
#define INODE_HH

namespace Node {

class LoadSpec;

class INode {
    virtual void getTaskId() = 0;

    virtual void loadData(const LoadSpec& spec) = 0;
};

}


#endif // INODE_HH
