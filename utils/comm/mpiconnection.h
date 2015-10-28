#ifndef MPICONNECTION_H
#define MPICONNECTION_H

#include "comm/icommunication.h"
#include <mpi.h>
#include <time.h>

template<class T>
class MpiConnection : public IComm<T>
{
public:
   MpiConnection();

   virtual void send(T* data, int dest);
   virtual void rec(int source, T *data);
   virtual void rec(T *data);
   virtual void broadcast(T* data, int root);

private:
   void getRandomTag();
   int mRandomTag;
   int probeData(const int source, int *sender, MPI_Status *status);

};

template<class T>
MpiConnection<T>::MpiConnection()
{

}

template<class T>
void MpiConnection<T>::send(T* data, int dest)
{
   getRandomTag();
   // tag =  1 is very special, it is just for send tag's tag
   MPI_Send(&mRandomTag, 1, MPI_INT, dest, IComm<T>::CONTROL_TAG, MPI_COMM_WORLD);
   int size = -1;
   const char *serilizedData = data->serialize(&size);
   MPI_Send(serilizedData, size, MPI_BYTE, dest, mRandomTag, MPI_COMM_WORLD);
}

template<class T>
void MpiConnection<T>::rec(int source, T* data)
{
   MPI_Status status;
   MPI_Recv(&mRandomTag, 1, MPI_INT, source, IComm<T>::CONTROL_TAG, MPI_COMM_WORLD, &status);

   int sender = -1;
   int size = probeData(source, &sender, &status);

   char* dataBuffer = new char[size];

   MPI_Recv(dataBuffer, size, MPI_BYTE, sender, mRandomTag, MPI_COMM_WORLD, &status);
   data->deserialize(dataBuffer);
   delete dataBuffer;
}

template<class T>
void MpiConnection<T>::rec(T* data)
{
   return rec(MPI_ANY_SOURCE, data);
}

template<class T>
void MpiConnection<T>::broadcast(T* data, int root)
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
      data->deserialize(dataBuffer);
   }
   else
   {
      const char *serilizedData = data->serialize(&size);
      assert(size > 0);
      // Firstly it needs to broadcast the size to all clients
      // so that they can have the buffer ready for receiving.
      MPI_Bcast(&size, 1, MPI_INT, root, MPI_COMM_WORLD);
      MPI_Bcast(const_cast<char*>(serilizedData), size, MPI_BYTE, root, MPI_COMM_WORLD);
   }

   delete dataBuffer;
}

template<class T>
int MpiConnection<T>::probeData(const int source, int* sender, MPI_Status *status)
{
   MPI_Probe(source, mRandomTag, MPI_COMM_WORLD, status);

   int size = -1;
   MPI_Get_count(status, MPI_BYTE, &size);
   *sender = status->MPI_SOURCE;

   assert(size != -1);

   return size;
}

template<class T>
void MpiConnection<T>::getRandomTag()
{
   srand(time(NULL));
   mRandomTag = rand() % 511523 + 1;
}

#endif // MPICONNECTION_H
