#include "mpiconnection.h"
#include <vector>



MpiConnection::MpiConnection()
{
    mComm = 0;
}


void MpiConnection::ssend(ISerializable *data, int dest)
{
    getRandomTag();
    // tag =  1 is very special, it is just for send tag's tag
    MPI_Send(&mRandomTag, 1, MPI_INT, dest, IComm::CONTROL_TAG, MPI_COMM_WORLD);
    data->getSerializerRef().clearContent();
    data->serialize();
    int size = data->getSerializer().getSize();
    const char *serilizedData = data->getSerializer().getPackedString();
    MPI_Send(const_cast<char *>(serilizedData), size, MPI_BYTE, dest, mRandomTag, MPI_COMM_WORLD);
}


void MpiConnection::rec(int source, ISerializable *data)
{
    MPI_Status status;
    MPI_Recv(&mRandomTag, 1, MPI_INT, source, IComm::CONTROL_TAG, MPI_COMM_WORLD, &status);

    int sender = -1;
    int size = probeData(source, &sender, &status);

    char dataBuffer[size];

    MPI_Recv(dataBuffer, size, MPI_BYTE, sender, mRandomTag, MPI_COMM_WORLD, &status);
    data->getSerializerRef().clearContent();
    data->getSerializerRef().setPackedString(dataBuffer);
    data->deserialize();
}


void MpiConnection::rec(ISerializable *data)
{
    return rec(MPI_ANY_SOURCE, data);
}


void MpiConnection::broadcast(ISerializable *data, int root)
{
    char* dataBuffer = NULL;
    int size = -1;

    if(ICommConfig::mRank != root)
    {
        int size  = -1;
        // Receive the size
        MPI_Bcast(&size, 1, MPI_INT, root, MPI_COMM_WORLD);
        assert(size >= 0);
        // Malloc enough size of memory
        dataBuffer = new char[size];
        MPI_Bcast(dataBuffer, size, MPI_BYTE, root, MPI_COMM_WORLD);
        //data->deserialize(dataBuffer);
        data->getSerializerRef().setPackedString(dataBuffer);
        data->deserialize();
    }
    else
    {
        data->serialize();
        size = data->getSerializer().getSize();
        const char *serilizedData = data->getSerializer().getPackedString();
        assert(size > 0);
        // Firstly it needs to broadcast the size to all clients
        // so that they can have the buffer ready for receiving.
        MPI_Bcast(&size, 1, MPI_INT, root, MPI_COMM_WORLD);
        MPI_Bcast(const_cast<char*>(serilizedData), size, MPI_BYTE, root, MPI_COMM_WORLD);
    }

    delete dataBuffer;
}

void MpiConnection::barrier()
{
    MPI_Barrier(*mComm);
}

void MpiConnection::setCommunicator(void *communicator)
{
    assert(communicator != NULL);
    mComm = static_cast<MPI_Comm*>(communicator);
}

void MpiConnection::gather(std::vector<ISerializable *>& data, ISerializable* sendData, unsigned int mpiSize)
{
    // Meaningless to gather from only himself!
    assert (mpiSize >= 2);

    sendData->serialize();
    int sendSize = sendData->getSerializer().getSize();

    char* dataBuffer = NULL;

    int sizeArray[mpiSize];

    MPI_Gather(&sendSize, 1, MPI_INT, sizeArray, 1, MPI_INT, ROOT_ID, *mComm);

    // Get the max size of the senders
    int chunkSize = sendSize;
    for (unsigned int i = 0; i < mpiSize; ++ i)
    {
        if(sizeArray[i] > chunkSize)
        {
            chunkSize = sizeArray[i];
        }
    }

    printf("Max chunkSize = [%d]\n", chunkSize);

    // Now we can new chunkSize * mpiSize recvbuffer

    dataBuffer = new char[chunkSize * mpiSize];
    MPI_Gather(const_cast<char *>(sendData->getSerializer().getPackedString()),
               sendSize,
               MPI_BYTE,
               dataBuffer,
               chunkSize,
               MPI_BYTE,
               ROOT_ID,
               *mComm);

    for(unsigned int i = 0; i < mpiSize; ++ i)
    {
        ISerializable* instance = data[i];
        instance->getSerializerRef().setPackedString(dataBuffer, chunkSize * i);
        instance->deserialize();
    }

    delete dataBuffer;
}

void MpiConnection::gather(ISerializable* data)
{
    data->serialize();
    int size = data->getSerializer().getSize();
    const char *serializedData = data->getSerializer().getPackedString();

    assert(size > 0);
    MPI_Gather(&size, 1, MPI_INT, NULL, 0, MPI_INT, ROOT_ID, *mComm);
    MPI_Gather(const_cast<char *>(serializedData), size, MPI_BYTE, NULL, 0, MPI_BYTE, ROOT_ID, *mComm);
}


int MpiConnection::probeData(const int source, int *sender, MPI_Status *status)
{
    MPI_Probe(source, mRandomTag, MPI_COMM_WORLD, status);

    int size = -1;
    MPI_Get_count(status, MPI_BYTE, &size);
    *sender = status->MPI_SOURCE;

    assert(size != -1);

    return size;
}


void MpiConnection::getRandomTag()
{
    srand(time(NULL));
    mRandomTag = rand() % 511523 + 1;
}
