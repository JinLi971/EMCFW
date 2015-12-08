#include "LoadSpec.hh"
#include <utils/serializer/GlobalClassId.hh>
#include <assert.h>

namespace DataSet
{
namespace Control
{

LoadSpec::LoadSpec(const std::string &configFilePath,
               int startIndex,
               int endIndex,
               const int controlId,
               const Executor::ExecutorType execType,
               const std::vector<int> &nodeCluster)
    : mConfigFilePath(configFilePath),
      mStartIndex(startIndex),
      mEndIndex(endIndex),
      mControlId(controlId),
      mExecutorType(execType),
      mNodeCluster(nodeCluster)
{
    mClassId = GlobalClassId::LOAD_SPEC;
}

LoadSpec::LoadSpec()
    : mConfigFilePath(""),
      mStartIndex(-1),
      mEndIndex(-1),
      mControlId(-1),
      mExecutorType(Executor::NONE)
{
    mClassId = GlobalClassId::LOAD_SPEC;
}


void LoadSpec::serialize()
{
    mSerializer << mClassId;
    mSerializer << mConfigFilePath;
    mSerializer << mStartIndex;
    mSerializer << mEndIndex;
    mSerializer << mControlId;
    mSerializer << (int)mExecutorType;
    // push in size of the node cluster
    mSerializer << (unsigned int) mNodeCluster.size();
    for (unsigned int i = 0; i < mNodeCluster.size(); ++ i)
    {
        mSerializer << mNodeCluster[i];
    }

    // push in size of the node group
    mSerializer << mGroup.size();
    std::map<int, int>::iterator mapIter = mGroup.begin();
    while(mapIter != mGroup.end())
    {
        mSerializer << mapIter->first;
        mSerializer << mapIter->second;

        ++ mapIter;
    }
}

void LoadSpec::deserialize()
{
    mNodeCluster.clear();

    mSerializer >> mClassId;
    assert (mClassId == GlobalClassId::LOAD_SPEC);

    mSerializer >> mConfigFilePath;
    mSerializer >> mStartIndex;
    mSerializer >> mEndIndex;
    mSerializer >> mControlId;

    int tmpExecutorType = -1;
    mSerializer >> tmpExecutorType;
    mExecutorType = (Executor::ExecutorType) tmpExecutorType;

    // get the size of node cluster
    int sizeOfNodeCluster = -1;
    mSerializer >> sizeOfNodeCluster;

    assert (sizeOfNodeCluster >= 0);
    mNodeCluster.reserve(sizeOfNodeCluster);

    for (int i = 0, tmp = -1; i < sizeOfNodeCluster; ++ i, tmp = -1)
    {
        mSerializer >> tmp;
        assert(tmp >= 0);
        mNodeCluster.push_back(tmp);
    }

    int sizeOfGroup = -1;
    mSerializer >> sizeOfGroup;

    assert (sizeOfGroup >= 0);

    for (int i = 0; i < sizeOfGroup; ++ i)
    {
        int color = -1;
        int key = -1;

        mSerializer >> color;
        mSerializer >> key;

        assert(color >= 0);

        mGroup.insert(std::make_pair<int, int>(color, key));
    }
}

}
}

