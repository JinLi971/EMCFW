#include "SlaveNodeTest.hh"
#include "node/slave/SlaveNode.hh"
#include "node/slave/ClusterHead.hh"
#include "node/NodeFactory.hh"
#include "dataset/executor/ExecutorType.hh"
#include "DebugHelper.hh"
#include "dataset/executor/MockContextAndResult.hh"

using namespace DataSet::Control;

SlaveNode::SlaveNode()
    : mNode(NULL),
      mTaskId(-1),
      mSize(-1)
{
    MPI_Comm_rank(MPI_COMM_WORLD, &mTaskId);
    MPI_Comm_size(MPI_COMM_WORLD, &mSize);

    mComm = MPI_COMM_WORLD;
    mConnection.setCommunicator(&mComm);
    mConnection.setRank(mTaskId);
}

void SlaveNode::SetUp()
{
    mNode = Node::NodeFactory::getNode(Node::NodeConstants::SLAVE, mTaskId);
    EXPECT_TRUE(mNode);

    mCmd.setContextType(DataSet::Executor::MOCK_CONTEXT);
    mCmd.setResultType(DataSet::Executor::MOCK_RESULT);
    DataSet::Executor::MockContext* context = (DataSet::Executor::MockContext *)mCmd.getContextPtr().get();
    DataSet::Executor::MockResult* result = (DataSet::Executor::MockResult *)mCmd.getResultPtr().get();

    context->setTestData("Mock Context Data");
    result->setTestData("Mock Result Data");

    mTestSpec.setConfigFilePath("./Test.conf");
    mTestSpec.setControlId(0);
    mTestSpec.setStartIndex(0);
    mTestSpec.setEndIndex(100);
    mTestSpec.setSmallIterationTime(100);
    mTestSpec.setExecutorType(DataSet::Executor::MOCK);

    std::map<int, LoadSpec::GroupStruct>& beforeGroup = mTestSpec.getGroup();
    std::vector<int> clusterVector {0, mTaskId};
    if(mTaskId == 0)
    {
        clusterVector.erase(clusterVector.begin());
    }
    LoadSpec::GroupStruct serializeGroup;

    serializeGroup.group = NULL;
    serializeGroup.comm = NULL;
    serializeGroup.cluster = clusterVector;
    serializeGroup.taskId = mTaskId;
    serializeGroup.color = 1;
    serializeGroup.controller = 0;

    beforeGroup[serializeGroup.color] = serializeGroup;

    EXPECT_TRUE(mTestSpec.getGroup()[serializeGroup.color] == serializeGroup);

    mNode->setLoadSpec(mTestSpec);
}

void SlaveNode::testSpecDeepCopy()
{
    mTestSpec.setConfigFilePath(".WrongFile.conf");
    mTestSpec.getGroup()[1].controller = 1;

    EXPECT_TRUE(mNode->getLoadSpec().getConfigFilePath() == "./Test.conf");
    EXPECT_TRUE(mNode->getLoadSpec().getGroup().at(1).controller == 0);
}

void SlaveNode::testLoadData()
{
    // Check init state before constructing group
    // All group comm and group should be NULL
    EXPECT_TRUE(!mNode->getLoadSpec().getGroup().at(1).comm);
    EXPECT_TRUE(!mNode->getLoadSpec().getGroup().at(1).group);

    mNode->loadData();
    EXPECT_EQ(1, Executor::ExecutorManager::getInstance()->getSizeofExecutors(DataSet::Executor::MOCK));

    // Check construct group correctly
    EXPECT_TRUE(mNode->getLoadSpec().getGroup().at(1).comm);
    EXPECT_TRUE(mNode->getLoadSpec().getGroup().at(1).group);
}

void SlaveNode::testCmd()
{
    // This is a mpi test

    if(mSize <= 1) return;
    testLoadData();

    if(mTaskId == 0)
    {
        // Root node will send out cmd
        // First set the context and result
        // And then die
        for(int i = 1; i < mSize; i ++)
        {
            mCmd.setInstruction(Node::INode::NEW_CONTEXT | Node::INode::NEW_RESULT);
            mConnection.setMode(IComm::SEND);
            mConnection.setData(&mCmd);
            mConnection.sync(i);

            mCmd.setInstruction(Node::INode::DIE);
            mConnection.setData(&mCmd);
            mConnection.sync(i);
        }
    } else
    {
        mNode->start();

        Node::Slave::SlaveNode* node = dynamic_cast<Node::Slave::SlaveNode*>(mNode);
        EXPECT_TRUE(node->getResult()->getType() == MOCK_RESULT);
        EXPECT_TRUE(node->getContext()->getType() == MOCK_CONTEXT);
        EXPECT_EQ("Mock Result Data", ((DataSet::Executor::MockResult *)node->getResultRef().get())->getTestData());
        EXPECT_EQ("Mock Context Data", ((DataSet::Executor::MockContext *)node->getContextRef().get())->getTestData());
        EXPECT_TRUE(Executor::ExecutorManager::getInstance()->getSizeofExecutors(DataSet::Executor::MOCK) == 0);
    }
}

void SlaveNode::TearDown()
{
    mNode->destory();
}

TEST_F(SlaveNode, testCloneCopy)
{
    testSpecDeepCopy();
}

TEST_F(SlaveNode, testLoadData)
{
    testLoadData();
}

TEST_F(SlaveNode, testSetAndKill)
{
    testCmd();
}
