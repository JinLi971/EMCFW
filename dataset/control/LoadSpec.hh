#ifndef CONFIG_HH
#define CONFIG_HH

#include <string>
#include <vector>
#include "utils/serializer/ISerializable.hh"
#include "dataset/executor/ExecutorType.hh"
#include <mpi.h>

namespace DataSet
{
namespace Control
{

class LoadSpec : public ISerializable
{
public:
    LoadSpec(const std::string& configFilePath,
               int startIndex,
               int endIndex,
               const int controlId,
               const Executor::ExecutorType execType,
               const std::vector<int>& nodeCluster);

    LoadSpec();

    struct GroupStruct
    {
        MPI_Group group;
        MPI_Comm comm;
        std::vector<int> cluster;
        int taskId;
        int color;
        int controller;

        virtual bool operator =(const GroupStruct& obj) {
            return color == obj.color;
        }

        int *getClusterList() {
            int* nodeListCpy = new int[cluster.size()];
            for(unsigned int i = 0; i < cluster.size(); ++ i) {
                nodeListCpy[i] = cluster[i];
            }

            return nodeListCpy;
        }

    };

    const std::string& getConfigFilePath() { return mConfigFilePath; }
    void setConfigFilePath(const std::string& configPath) { mConfigFilePath = configPath; }

    int getStartIndex() { return mStartIndex; }
    void setStartIndex(int value) { mStartIndex = value; }

    int getEndIndex() { return mEndIndex; }
    void setEndIndex(int value) { mEndIndex = value; }

    int getControlId() { return mControlId; }
    void setControlId(int value) { mControlId = value; }

    int *getNodeCluster(int groupId) {
        if(!mGroup.count(groupId))
            return NULL;

        return mGroup[groupId].getClusterList();
    }

    void setExecutorType(Executor::ExecutorType type) { mExecutorType = type; }
    Executor::ExecutorType getExecutorType() { return mExecutorType; }

    int getSmallIterationTime() { return mSmallIterationTime; }
    void setSmallIterationTime(int value) { mSmallIterationTime = value; }

    const std::map<int, GroupStruct>& getGroup() const { return mGroup; }
    std::map<int, GroupStruct>& getGroup() { return mGroup; }

    int getGroupTaskId(int groupColor) {
        if(!mGroup.count(groupColor))
            return -1;

        return mGroup[groupColor].taskId;
    }

protected:
    std::string mConfigFilePath;
    int mStartIndex;
    int mEndIndex;
    int mControlId;
    int mSmallIterationTime;
    Executor::ExecutorType mExecutorType;
    std::map<int, GroupStruct> mGroup;

    // ISerializable interface
public:
    void serialize();
    void deserialize();
};

}
}
#endif // CONFIG_HH
