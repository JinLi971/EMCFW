#ifndef ICOMMUNICATION_HH
#define ICOMMUNICATION_HH

#include "icommconfig.h"
#include <mpi.h>
#include <assert.h>

#include "utils/serializer/ISerializable.hh"

class IData;

class IComm : public ICommConfig
{
public:
   virtual ~IComm() {}

   virtual void sync(ISerializable* data, int dest = -1, int root = -1, int source = MPI_ANY_SOURCE)
   {
      switch (mMode)
      {
         case BROADCAST:
         {
            assert (root >= 0);
            broadcast(data, root);
            break;
         }
         case SEND:
         {
            assert (dest >= 0);
            send(data, dest);
            break;
         }
         case REC:
         {
            rec(source, data);
            break;
         }
         default:
         {
            printf("Rank = [%d] Something wrong, Specify the mode first\n", mRank);
         }
      }
   }

protected:
   virtual void send(ISerializable* data, int dest) = 0;
   virtual void rec(int source, ISerializable *data) = 0;
   virtual void rec(ISerializable *data) = 0;
   virtual void broadcast(ISerializable* data, int root) = 0;

protected:
   enum
   {
      CONTROL_TAG = 1,
      CONTROL_BROADCAST_TAG = 2
   };

};

#endif // ICOMMUNICATION_HH
