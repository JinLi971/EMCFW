#ifndef SLAVENODETEST_HH
#define SLAVENODETEST_HH
#include <gtest/gtest.h>
#include "node/INode.hh"
#include "dataset/control/LoadSpec.hh"
#include "dataset/control/NodeInstructionData.hh"

#include "utils/comm/mpiconnection.h"

class SlaveNode : public ::testing::Test
{
public:
    SlaveNode();

    void SetUp();
    void TearDown();

    void testSpecDeepCopy();
    void testLoadData();
    void testCmd();
private:
    MpiConnection mConnection;
    Node::INode* mNode;
    int mTaskId;
    int mSize;
    MPI_Comm mComm;


    DataSet::Control::LoadSpec mTestSpec;
    DataSet::Control::NodeInstructionData mCmd;
};

#endif // SLAVENODETEST_HH
