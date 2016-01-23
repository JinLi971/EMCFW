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
               const Executor::ExecutorType execType);

    LoadSpec();

    struct GroupStruct
    {
        MPI_Group group;
        MPI_Comm comm;
        std::vector<int> cluster;
        int taskId;
        int color;
        int controller;

        virtual bool operator ==(const GroupStruct& obj) {
            return color == obj.color;
        }

        int *getClusterList() {
            int* nodeListCpy = new int[cluster.size()];
            for(unsigned int i = 0; i < cluster.size(); ++ i) {
                nodeListCpy[i] = cluster[i];
            }

            return nodeListCpy;
        }

        inline virtual void operator =(const GroupStruct& rhs) {
            group = rhs.group;
            comm = rhs.comm;
            cluster = rhs.cluster;
            taskId = rhs.taskId;
            color = rhs.color;
            controller = rhs.controller;
        }

    };

    const std::string& getConfigFilePath() const { return mConfigFilePath; }
    void setConfigFilePath(const std::string& configPath) { mConfigFilePath = configPath; }

    int getStartIndex() { return mStartIndex; }
    void setStartIndex(int value) { mStartIndex = value; }

    int getEndIndex() { return mEndIndex; }
    void setEndIndex(int value) { mEndIndex = value; }

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

    int getGroupController(int groupColor) {
        if(!mGroup.count(groupColor))
            // Fall back to Use Root as Controller
            return 0;

        return mGroup[groupColor].controller;
    }

    const GroupStruct& getGroupStruct(int color) const
    {
        return mGroup.at(color);
    }

    MPI_Comm *getGroupComm(int color)
    {
        if(!mGroup.count(color))
            return nullptr;

        return &mGroup[color].comm;
    }

    int getDefaultGroup() const;
    void setDefaultGroup(int value);

protected:
    std::string mConfigFilePath;
    int mStartIndex;
    int mEndIndex;
    int mSmallIterationTime;
    Executor::ExecutorType mExecutorType;
    std::map<int, GroupStruct> mGroup;
    int mDefaultGroup;

    // ISerializable interface
public:
    void serialize();
    void deserialize();

};

}
}
#endif // CONFIG_HH
