#ifndef MASTERNODE_HH
#define MASTERNODE_HH

#include "../../dataset/FrameList.hh"


namespace Node {
namespace Master {

class MasterNode
{
public:
    MasterNode();

private:
    DataSet::FrameList* mFrameList;
};

} //Master NS
} //Node NS


#endif // MASTERNODE_HH
