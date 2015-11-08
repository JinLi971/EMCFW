#include "TestSerialization.hh"
#include <gtest.h>
#include "../../../dataset/control/LoadSpec.hh"

TestSerialization::TestSerialization()
{
}

void TestSerialization::SetUp()
{

}

void TestSerialization::TearDown()
{

}

TEST(TestSerialization, testLoadSpec)
{
    DataSet::Control::LoadSpec before;

    before.setConfigFilePath("/tmp/fakedPath.conf");
    before.setControlId(1);
    before.setStartIndex(1);
    before.setEndIndex(100);
    before.getNodeClusterRef().push_back(0);
    before.getNodeClusterRef().push_back(1);
    before.getNodeClusterRef().push_back(2);

    before.serialize();
    const char * result = before.getSerializer().getPackedString();

    DataSet::Control::LoadSpec after;
    after.getSerializerRef().setPackedString(result);

    after.deserialize();

    EXPECT_EQ (before.getConfigFilePath().compare(after.getConfigFilePath()), 0);
    EXPECT_EQ (before.getControlId(), after.getControlId());
    EXPECT_EQ (before.getStartIndex(), after.getStartIndex());
    EXPECT_EQ (before.getEndIndex(), after.getEndIndex());
    EXPECT_EQ (before.getNodeCluster().size(), after.getNodeCluster().size());
    EXPECT_EQ (before.getNodeCluster()[0], after.getNodeCluster()[0]);
    EXPECT_EQ (before.getNodeCluster()[1], after.getNodeCluster()[1]);
    EXPECT_EQ (before.getNodeCluster()[2], after.getNodeCluster()[2]);
}

