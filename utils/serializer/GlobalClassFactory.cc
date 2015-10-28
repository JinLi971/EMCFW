#include "GlobalClassFactory.hh"

#include "GlobalClassId.hh"

GlobalClassFactory::GlobalClassFactory()
{
}


GlobalClassFactory &GlobalClassFactory::getInstance()
{
    if(!mInstance)
        mInstance = new GlobalClassFactory();

    return *mInstance;
}


