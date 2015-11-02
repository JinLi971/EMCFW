#ifndef ICOMMCONFIG_H
#define ICOMMCONFIG_H

class ICommConfig
{
public:
   typedef enum
   {
      IDLE = 0,
      BROADCAST,
      SEND,
      REC
   }Mode;

   virtual Mode getMode() { return mMode; }
   virtual void setMode(Mode value) { mMode = value; }

   virtual void setRank (int value) { mRank = value; }
   virtual int getRank () { return mRank; }

protected:
   Mode mMode;
   int mRank;
};

#endif // ICOMMCONFIG_H
