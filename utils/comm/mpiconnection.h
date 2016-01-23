#ifndef MPICONNECTION_H
#define MPICONNECTION_H

#include "icommunication.h"
#include <mpi.h>
#include <time.h>
#include <cstdlib>
#include <vector>

class MpiConnection : public IComm
{
public:
   MpiConnection();

   virtual void ssend(ISerializable *data, int dest);
   virtual void rec(int source, ISerializable *data);
   virtual void rec(ISerializable *data);
   virtual void broadcast(ISerializable *data, int root);
   virtual void barrier();
   virtual void setCommunicator(void* communicator);
   virtual void gather(std::vector<ISerializable *> &data, ISerializable *sendData, unsigned int mpiSize);
   virtual void gather(ISerializable *data);
private:
   void getRandomTag();
   int mRandomTag;
   int probeData(const int source, int *sender, MPI_Status *status);

private:
   MPI_Comm* mComm;

};


#endif // MPICONNECTION_H
