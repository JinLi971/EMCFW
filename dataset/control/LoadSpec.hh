#ifndef CONFIG_HH
#define CONFIG_HH

#include <string>
#include <vector>
#include "utils/serializer/ISerializable.hh"
#include "dataset/executor/ExecutorType.hh"

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
               const int controlId, const Executor::ExecutorType execType,
               const std::vector<int>& nodeCluster);

    LoadSpec();

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

protected:
    std::string mConfigFilePath;
    int mStartIndex;
    int mEndIndex;
    int mControlId;
    Executor::ExecutorType mExecutorType;
    std::vector<int> mNodeCluster;


    // ISerializable interface
public:
    void serialize();
    void deserialize();
};

}
}
#endif // CONFIG_HH
