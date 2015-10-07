#include "NodeFactory.hh"

namespace Node {

INode *NodeFactory::getNode(NodeConstants::NodeType type)
{
        switch (type) {
            case NodeConstants::MASTER:
            {
                return 0;
            }
            case NodeConstants::SLAVE:
            {
                return 0;
            }
            default:
            {
                return 0;
            }
        }
}

}
