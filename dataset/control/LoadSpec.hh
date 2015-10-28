#ifndef CONFIG_HH
#define CONFIG_HH

#include <string>
#include <vector>

namespace DataSet
{
namespace Control
{

class Config
{
public:
    Config(const std::string& configFilePath,
               int startIndex,
               int endIndex,
               int controlId,
               const std::vector<int>& nodeCluster);

    const std::string& getConfigFilePath() { return mConfigFilePath; }
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
    std::vector<int> mNodeCluster;

};

}
}
#endif // CONFIG_HH