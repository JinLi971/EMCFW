#ifndef TESTSERIALIZATION_HH
#define TESTSERIALIZATION_HH

#include <gtest/gtest.h>
#include "../../../utils/serializer/ISerializable.hh"
#include "../../../utils/serializer/serializationbase.h"

class TestSerialization : public ::testing::Test
{
public:
    TestSerialization();
    ~TestSerialization() {}
protected:
    void SetUp();
    void TearDown();

private:
    SerializationBase mSerializer;
};

#endif // TESTSERIALIZATION_HH
