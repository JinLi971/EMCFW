#include "LoadSpec.hh"
#include <utils/serializer/GlobalClassId.hh>

namespace DataSet
{
namespace Control
{

LoadSpec::LoadSpec(const std::string &configFilePath,
               int startIndex,
               int endIndex,
               int controlId,
               const std::vector<int> &nodeCluster)
    : mClassId(GlobalClassId::LOAD_SPEC),
      mConfigFilePath(configFilePath),
      mStartIndex(startIndex),
      mEndIndex(endIndex),
      mControlId(controlId),
      mNodeCluster(nodeCluster)
{

}

void LoadSpec::serialize()
{
    mSerializer << mClassId;
    mSerializer << mConfigFilePath;
    mSerializer << mStartIndex;
    mSerializer << mEndIndex;
    mSerializer << mControlId;
    // push in size of the node cluster
    mSerializer << (unsigned int) mNodeCluster.size();
    for (int i = 0; i < mNodeCluster.size(); ++ i)
    {
        mSerializer << mNodeCluster[i];
    }
}

void LoadSpec::deserialize()
{
    mSerializer >> mClassId;
    assert (mClassId == GlobalClassId::LOAD_SPEC);

    mSerializer >> mConfigFilePath;
    mSerializer >> mStartIndex;
    mSerializer >> mEndIndex;
    mSerializer >> mControlId;

    // get the size of node cluster
    int sizeOfNodeCluster = -1;
    mSerializer >> sizeOfNodeCluster;

    assert (sizeOfNodeCluster >= 0);
    mNodeCluster.reserve(sizeOfNodeCluster);

    for (int i = 0, tmp = -1; i < sizeOfNodeCluster; ++ i, tmp = -1)
    {
        mSerializer >> tmp;
        mNodeCluster.push_back(tmp);
    }
}

}
}

