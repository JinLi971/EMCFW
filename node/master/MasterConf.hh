#ifndef MASTERCONF_HH
#define MASTERCONF_HH

#include <string>
#include "utils/serializer/serializationbase.h"
#include "utils/serializer/ISerializable.hh"

namespace Node {
namespace Master {

class MasterConf : public ISerializable
{
public:
    MasterConf();

    std::string dataFileDir;
    int dataStartIndex;
    int dataEndIndex;
    unsigned int dispatchStrategy;

    // ISerializable interface
public:
    virtual void serialize();
    virtual void deserialize();
};

}
}


#endif // MASTERCONF_HH
