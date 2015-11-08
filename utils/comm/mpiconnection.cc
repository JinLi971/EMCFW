#include "mpiconnection.h"



MpiConnection::MpiConnection()
{

}


void MpiConnection::send(ISerializable *data, int dest)
{
    getRandomTag();
    // tag =  1 is very special, it is just for send tag's tag
    MPI_Send(&mRandomTag, 1, MPI_INT, dest, IComm::CONTROL_TAG, MPI_COMM_WORLD);
    data->serialize();
    int size = data->getSerializer().getSize();
    const char *serilizedData = data->getSerializer().getPackedString();
    MPI_Send(serilizedData, size, MPI_BYTE, dest, mRandomTag, MPI_COMM_WORLD);
}


void MpiConnection::rec(int source, ISerializable *data)
{
    MPI_Status status;
    MPI_Recv(&mRandomTag, 1, MPI_INT, source, IComm::CONTROL_TAG, MPI_COMM_WORLD, &status);

    int sender = -1;
    int size = probeData(source, &sender, &status);

    char* dataBuffer = new char[size];

    MPI_Recv(dataBuffer, size, MPI_BYTE, sender, mRandomTag, MPI_COMM_WORLD, &status);
    data->getSerializerRef().setPackedString(dataBuffer);
    data->deserialize();
    delete dataBuffer;
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
    assert(mComm != NULL);
    mComm = static_cast<MPI_Comm*>(communicator);
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
