#include "NodeFactory.hh"

#include "node/master/MasterNode.hh"
#include "node/slave/SlaveNode.hh"
#include "node/master/SlaveAgent.hh"

namespace Node {

INode *NodeFactory::getNode(NodeConstants::NodeType type, int taskId)
{
        switch (type) {
            case NodeConstants::MASTER:
            {
                return new Master::MasterNode(taskId);
            }
            case NodeConstants::SLAVE_AGENT:
            {
                return new Master::SlaveAgent(taskId);
            }
            case NodeConstants::SLAVE:
            {
                return new Slave::SlaveNode(taskId);
            }
            default:
            {
                return 0;
            }
        }
}

}
