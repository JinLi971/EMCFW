#ifndef ISERIALIZABLE_HH
#define ISERIALIZABLE_HH

#include "serializationbase.h"
#include "GlobalClassId.hh"

#include <string>

class ISerializable
{
public:
    virtual void serialize() = 0;
    virtual void deserialize() = 0;

    virtual GlobalClassId::ClassId getClassId() { return mClassId; }
    virtual const SerializationBase& getSerializer() { return mSerializer; }
    virtual SerializationBase& getSerializerRef() { return mSerializer; }

protected:
    GlobalClassId::ClassId mClassId;
    SerializationBase mSerializer;
};

#endif // ISERIALIZABLE_HH
