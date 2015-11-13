#include "TestMpiConnection.hh"
#include "../../../dataset/control/LoadSpec.hh"
#include <mpi.h>


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
    mBeforeSend.setControlId(1);
    mBeforeSend.setStartIndex(1);
    mBeforeSend.setEndIndex(100);
    mBeforeSend.getNodeClusterRef().push_back(0);
    mBeforeSend.getNodeClusterRef().push_back(1);
    mBeforeSend.getNodeClusterRef().push_back(2);

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
    EXPECT_EQ (expected.getControlId(), actual.getControlId());
    EXPECT_EQ (expected.getStartIndex(), actual.getStartIndex());
    EXPECT_EQ (expected.getEndIndex(), actual.getEndIndex());
    EXPECT_EQ (expected.getNodeCluster().size(), actual.getNodeCluster().size());
    EXPECT_EQ (expected.getNodeCluster()[0], actual.getNodeCluster()[0]);
    EXPECT_EQ (expected.getNodeCluster()[1], actual.getNodeCluster()[1]);
    EXPECT_EQ (expected.getNodeCluster()[2], actual.getNodeCluster()[2]);
}

void TestMpiConnection::testBasicSendRecv()
{
    if (mTaskId == 0)
    {
        mConnection.setMode(IComm::SEND);
        mConnection.setData(&mBeforeSend);
        mConnection.sync(mTaskId + 1);
    }

    if (mTaskId == 1)
    {
        mConnection.setMode(IComm::REC);
        mConnection.setData(&mAfterSend);
        mConnection.sync();
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
        mAfterSend.setControlId(100);
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
