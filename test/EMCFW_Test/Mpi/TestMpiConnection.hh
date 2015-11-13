#ifndef TESTMPICONNECTION_HH
#define TESTMPICONNECTION_HH

#include <gtest/gtest.h>

#include "../../utils/comm/mpiconnection.h"
#include "../../dataset/control/LoadSpec.hh"

class TestMpiConnection : public ::testing::Test
{
public:
    TestMpiConnection();

    void SetUp();
    void TearDown();

    void testBasicSendRecv();
    void testBasicBroadcast();

public:
    MpiConnection mConnection;
    int mTaskId;
    MPI_Comm mComm;
    int mSize;

    DataSet::Control::LoadSpec mBeforeSend;
    DataSet::Control::LoadSpec mAfterSend;

    void testGather();
private:
    void compareResult(DataSet::Control::LoadSpec &expected,
                       DataSet::Control::LoadSpec &actual);
};

#endif // TESTMPICONNECTION_HH
