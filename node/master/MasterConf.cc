#include "MasterConf.hh"
#include <assert.h>


namespace Node {
namespace Master {

MasterConf::MasterConf()
{
    mClassId = GlobalClassId::MASTER_CONF;
}

void MasterConf::serialize()
{
    mSerializer << mClassId;
    mSerializer << dataFileDir;
    mSerializer << dataStartIndex;
    mSerializer << dataEndIndex;
    mSerializer << dispatchStrategy;
}

void MasterConf::deserialize()
{
    mSerializer >> mClassId;
    assert(mClassId == GlobalClassId::MASTER_CONF);
    mSerializer >> dataFileDir;
    mSerializer >> dataStartIndex;
    mSerializer >> dataEndIndex;
    mSerializer >> dispatchStrategy;
}

}
}
