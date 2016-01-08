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
      mExecutorType(execType)
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

    // push in size of the node group
    mSerializer << mGroup.size();
    std::map<int, GroupStruct>::iterator mapIter = mGroup.begin();
    while(mapIter != mGroup.end())
    {
        mSerializer << mapIter->second.color;
        mSerializer << mapIter->second.taskId;
        mSerializer << mapIter->second.controller;
        // push in size of the node cluster
        mSerializer << (unsigned int) mGroup[mapIter->second.color].cluster.size();
        for (unsigned int i = 0; i < mGroup[mapIter->second.color].cluster.size(); ++ i)
        {
            mSerializer << mGroup[mapIter->second.color].cluster[i];
        }

        ++ mapIter;
    }
}

void LoadSpec::deserialize()
{
    mGroup.clear();

    mSerializer >> mClassId;
    assert (mClassId == GlobalClassId::LOAD_SPEC);

    mSerializer >> mConfigFilePath;
    mSerializer >> mStartIndex;
    mSerializer >> mEndIndex;
    mSerializer >> mControlId;

    int tmpExecutorType = -1;
    mSerializer >> tmpExecutorType;
    mExecutorType = (Executor::ExecutorType) tmpExecutorType;

    int sizeOfGroup = -1;
    mSerializer >> sizeOfGroup;

    assert (sizeOfGroup >= 0);

    for (int i = 0; i < sizeOfGroup; ++ i)
    {
        GroupStruct group;

        mSerializer >> group.color;
        mSerializer >> group.taskId;
        mSerializer >> group.controller;
        // get the size of node cluster
        int sizeOfNodeCluster = -1;
        mSerializer >> sizeOfNodeCluster;
        assert (sizeOfNodeCluster >= 0);
        group.cluster.reserve(sizeOfNodeCluster);

        for (int i = 0, tmp = -1; i < sizeOfNodeCluster; ++ i, tmp = -1)
        {
            mSerializer >> tmp;
            assert(tmp >= 0);
            group.cluster.push_back(tmp);
        }

        assert(group.color >= 0);
        assert(!mGroup.count(group.color));
        mGroup[group.color] = group;
    }
}

}
}

