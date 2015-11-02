#include "SpImageSerializer.h"

SpImageSerializer::SpImageSerializer()
   : SerializationBase(SPIMAGE),
     mIsArrayStart(false),
     mArrayLength(0)
{
}
