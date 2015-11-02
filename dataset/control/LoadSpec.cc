#include "Config.hh"

namespace DataSet
{
namespace Control
{

Config::Config(const std::string &configFilePath,
               int startIndex,
               int endIndex,
               int controlId,
               const std::vector<int> &nodeCluster)
    : mConfigFilePath(configFilePath),
      mStartIndex(startIndex),
      mEndIndex(endIndex),
      mControlId(controlId),
      mNodeCluster(nodeCluster)
{

}




}
}

