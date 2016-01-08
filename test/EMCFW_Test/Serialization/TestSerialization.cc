#include "TestSerialization.hh"
#include <gtest/gtest.h>
#include "../../../dataset/control/LoadSpec.hh"
#include "../../../node/master/MasterConf.hh"
#include "../../../dataset/executor/ExecutorType.hh"

using namespace DataSet::Control;
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
    printf("Testing LoadSpec\n");
    DataSet::Control::LoadSpec before;

    before.setConfigFilePath("/tmp/fakedPath.conf");
    before.setControlId(1);
    before.setStartIndex(1);
    before.setEndIndex(100);
    before.setExecutorType(DataSet::Executor::MOCK);

    std::map<int, LoadSpec::GroupStruct>& beforeGroup = before.getGroup();
    std::vector<int> clusterVector {1, 2, 3};
    LoadSpec::GroupStruct serializeGroup;

    serializeGroup.group = NULL;
    serializeGroup.comm = NULL;
    serializeGroup.cluster = clusterVector;
    serializeGroup.taskId = 1;
    serializeGroup.color = 1;
    serializeGroup.controller = 1;

    beforeGroup[serializeGroup.color] = serializeGroup;

    before.serialize();
    const char * result = before.getSerializer().getPackedString();

    DataSet::Control::LoadSpec after;
    after.getSerializerRef().setPackedString(result);

    after.deserialize();

    EXPECT_EQ (before.getConfigFilePath().compare(after.getConfigFilePath()), 0);
    EXPECT_EQ (before.getControlId(), after.getControlId());
    EXPECT_EQ (before.getStartIndex(), after.getStartIndex());
    EXPECT_EQ (before.getEndIndex(), after.getEndIndex());
    EXPECT_EQ (before.getExecutorType(), after.getExecutorType());

    const LoadSpec::GroupStruct& afterGroup = after.getGroup()[serializeGroup.color];

    EXPECT_EQ (serializeGroup.cluster.size(), afterGroup.cluster.size());
    EXPECT_EQ (serializeGroup.cluster[0], afterGroup.cluster[0]);
    EXPECT_EQ (serializeGroup.cluster[1], afterGroup.cluster[1]);
    EXPECT_EQ (serializeGroup.cluster[2], afterGroup.cluster[2]);
    EXPECT_EQ (serializeGroup.color, afterGroup.color);
    EXPECT_EQ (serializeGroup.controller, afterGroup.controller);
    EXPECT_EQ (serializeGroup.taskId, afterGroup.taskId);
}

TEST(TestSerialization, testMasterConf)
{
    Node::Master::MasterConf before;

    before.dataStartIndex = 1;
    before.dataEndIndex = 100;
    before.dataFileDir = "/tmp/fakedDir";
    before.dispatchStrategy = 12;

    before.serialize();
    const char * result = before.getSerializer().getPackedString();

    Node::Master::MasterConf after;

    after.getSerializerRef().setPackedString(result);

    after.deserialize();

    EXPECT_EQ (before.dataStartIndex, after.dataStartIndex);
    EXPECT_EQ (before.dataEndIndex, after.dataEndIndex);
    EXPECT_EQ (before.dataFileDir.compare(after.dataFileDir), 0);
    EXPECT_EQ (before.dispatchStrategy, after.dispatchStrategy);
}

