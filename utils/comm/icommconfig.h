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
        REC,
        GATHER_ROOT,
        GATHER_CLIENT
    }Mode;

    const static int ROOT_ID = 0;

    virtual Mode getMode() { return mMode; }
    virtual void setMode(Mode value) { mMode = value; }

    virtual void setRank (int value) { mRank = value; }
    virtual int getRank () { return mRank; }

protected:
    Mode mMode;
    int mRank;
};

#endif // ICOMMCONFIG_H
