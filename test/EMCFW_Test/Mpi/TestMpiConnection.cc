#include "TestMpiConnection.hh"
#include "../../../dataset/control/LoadSpec.hh"
#include <mpi.h>

using namespace DataSet::Control;

TestMpiConnection::TestMpiConnection()
    : mTaskId(-1),
      mComm(MPI_COMM_WORLD),
      mSize(-1)
{
    MPI_Comm_rank(MPI_COMM_WORLD, &mTaskId);
    MPI_Comm_size(MPI_COMM_WORLD, &mSize);

    mConnection.setCommunicator(&mComm);
    mConnection.setRank(mTaskId);
}

void TestMpiConnection::SetUp()
{
    // Clear all contents for clean start
    mBeforeSend.getSerializerRef().clearContent();
    mAfterSend.getSerializerRef().clearContent();

    mBeforeSend.setConfigFilePath("/tmp/fakedPath.conf");
    mBeforeSend.setStartIndex(1);
    mBeforeSend.setEndIndex(100);

    std::map<int, LoadSpec::GroupStruct>& beforeGroup = mBeforeSend.getGroup();
    std::vector<int> clusterVector {0, 1, 2};
    LoadSpec::GroupStruct serializeGroup;

    serializeGroup.group = NULL;
    serializeGroup.comm = NULL;
    serializeGroup.cluster = clusterVector;
    serializeGroup.taskId = 1;
    serializeGroup.color = 1;
    serializeGroup.controller = 1;

    beforeGroup[serializeGroup.color] = serializeGroup;

    // All task will be in same group.
    mConnection.barrier();
}

void TestMpiConnection::TearDown()
{
    // Make sure all clients are synced before running next client
    mConnection.barrier();
}

void TestMpiConnection::compareResult(DataSet::Control::LoadSpec& expected,
                                      DataSet::Control::LoadSpec& actual)
{
    EXPECT_EQ (expected.getConfigFilePath().compare(actual.getConfigFilePath()), 0);
    EXPECT_EQ (expected.getStartIndex(), actual.getStartIndex());
    EXPECT_EQ (expected.getEndIndex(), actual.getEndIndex());

    const LoadSpec::GroupStruct& serializeGroup = expected.getGroup()[1];
    const LoadSpec::GroupStruct& afterGroup = actual.getGroup()[serializeGroup.color];

    EXPECT_EQ (serializeGroup.cluster.size(), afterGroup.cluster.size());
    EXPECT_EQ (serializeGroup.cluster[0], afterGroup.cluster[0]);
    EXPECT_EQ (serializeGroup.cluster[1], afterGroup.cluster[1]);
    EXPECT_EQ (serializeGroup.cluster[2], afterGroup.cluster[2]);
    EXPECT_EQ (serializeGroup.color, afterGroup.color);
    EXPECT_EQ (serializeGroup.controller, afterGroup.controller);
    EXPECT_EQ (serializeGroup.taskId, afterGroup.taskId);
}

void TestMpiConnection::testBasicSendRecv()
{
    if (mTaskId == 0)
    {
        for(int i = 1; i < mSize; ++i)
        {
            mConnection.setMode(IComm::SSEND);
            mConnection.setData(&mBeforeSend);
            mBeforeSend.setEndIndex(i);
            mConnection.sync(i);

            mConnection.setMode(IComm::REC);
            mConnection.setData(&mAfterSend);
            mConnection.sync(i);
        }
    } else
    {
        mConnection.setMode(IComm::REC);
        mConnection.setData(&mAfterSend);
        mConnection.sync();

        mConnection.setMode(IComm::SSEND);
        mConnection.setData(&mAfterSend);
        mConnection.sync(0);

        mBeforeSend.setEndIndex(mTaskId);

        compareResult(mBeforeSend, mAfterSend);
    }
}

void TestMpiConnection::testBasicBroadcast()
{
    mConnection.setMode(IComm::BROADCAST);

    // Broadcast from root
    if(mTaskId == 0)
    {
        printf ("Broadcast from [%d]\n", mTaskId);
        mConnection.sync(&mBeforeSend, -1, mTaskId);
    } else {
        mConnection.sync(&mAfterSend, -1, 0);
        compareResult(mBeforeSend, mAfterSend);
    }

    // Broadcast from slave
    if(mTaskId == mSize - 1)
    {
        printf ("Broadcast from [%d]\n", mTaskId);
        mConnection.sync(&mBeforeSend, -1, mTaskId);
    } else {
        mConnection.sync(&mAfterSend, -1, mSize - 1);
        compareResult(mBeforeSend, mAfterSend);
    }
}

void TestMpiConnection::testGather()
{
    if(mTaskId == 0)
    {
        mConnection.setMode(IComm::GATHER_ROOT);
        std::vector<ISerializable* > dataVector;

        for(int i = 0; i < mSize; ++ i)
        {
            dataVector.push_back(new DataSet::Control::LoadSpec());
        }

        mConnection.setVectorData(&dataVector);
        mConnection.setData(&mBeforeSend);
        mConnection.sync();

        for(int i = 0; i < mSize; ++ i)
        {
            compareResult(mBeforeSend,
                          *(dynamic_cast<DataSet::Control::LoadSpec *>(dataVector[i])));
        }
    } else {
        mConnection.setMode(IComm::GATHER_CLIENT);

        mConnection.setData(&mBeforeSend);
        mConnection.sync();
    }
}


TEST_F(TestMpiConnection, testSendRecv)
{
    if (mSize == 1) return;
    testBasicSendRecv();
}

TEST_F(TestMpiConnection, testBroadcast)
{
    if (mSize == 1) return;
    testBasicBroadcast();
}

TEST_F(TestMpiConnection, testGather)
{
    if(mSize == 1) return;
    testGather();
}
