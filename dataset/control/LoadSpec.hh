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
        int taskId;
        int color;

        virtual bool operator =(const GroupStruct& obj) {
            return color == obj.color;
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

    const std::vector<int>& getNodeCluster() { return mNodeCluster; }
    std::vector<int>& getNodeClusterRef() { return mNodeCluster; }

    void setExecutorType(Executor::ExecutorType type) { mExecutorType = type; }
    Executor::ExecutorType getExecutorType() { return mExecutorType; }

    int getSmallIterationTime() { return mSmallIterationTime; }
    void setSmallIterationTime(int value) { mSmallIterationTime = value; }

    const std::vector<GroupStruct>& getGroupMap() { return mGroup; }


    const int getGroupTaskId(int groupColor) {
        for(auto ele : mGroup) {
            if(ele.color == groupColor)
                return ele.taskId;
        }
    }

protected:
    std::string mConfigFilePath;
    int mStartIndex;
    int mEndIndex;
    int mControlId;
    int mSmallIterationTime;
    Executor::ExecutorType mExecutorType;
    std::vector<int> mNodeCluster;
    std::vector<GroupStruct> mGroup;

    // ISerializable interface
public:
    void serialize();
    void deserialize();
};

}
}
#endif // CONFIG_HH
