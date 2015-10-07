#ifndef NODEFACTORY_HH
#define NODEFACTORY_HH

#include "NodeConstants.hh"
#include "INode.hh"

namespace Node {

class NodeFactory
{
public:
    static INode* getNode(NodeConstants::NodeType type);

private:
    NodeFactory() {}
    virtual void operator=(const NodeFactory&) {}
};

}


#endif // NODEFACTORY_HH
