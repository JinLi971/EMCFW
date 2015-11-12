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

void TestMpiConnection::compareResult()
{
    EXPECT_EQ (mBeforeSend.getConfigFilePath().compare(mAfterSend.getConfigFilePath()), 0);
    EXPECT_EQ (mBeforeSend.getControlId(), mAfterSend.getControlId());
    EXPECT_EQ (mBeforeSend.getStartIndex(), mAfterSend.getStartIndex());
    EXPECT_EQ (mBeforeSend.getEndIndex(), mAfterSend.getEndIndex());
    EXPECT_EQ (mBeforeSend.getNodeCluster().size(), mAfterSend.getNodeCluster().size());
    EXPECT_EQ (mBeforeSend.getNodeCluster()[0], mAfterSend.getNodeCluster()[0]);
    EXPECT_EQ (mBeforeSend.getNodeCluster()[1], mAfterSend.getNodeCluster()[1]);
    EXPECT_EQ (mBeforeSend.getNodeCluster()[2], mAfterSend.getNodeCluster()[2]);
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
        compareResult();
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
        compareResult();
    }

    // Broadcast from slave
    if(mTaskId == mSize - 1)
    {
        printf ("Broadcast from [%d]\n", mTaskId);
        mConnection.sync(&mBeforeSend, -1, mTaskId);
    } else {
        mConnection.sync(&mAfterSend, -1, mSize - 1);
        compareResult();
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
