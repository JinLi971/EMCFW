#ifndef INODE_HH
#define INODE_HH

#include "dataset/control/LoadSpec.hh"

namespace Node {

class INode {

public:
    virtual int getTaskId() const = 0;
    virtual void setTaskId(int value) = 0;

    /**
     * @brief getLoadSpec return the LoadSpec of the slave node
     * @return
     */
    virtual const DataSet::Control::LoadSpec& getLoadSpec() = 0;

    /**
     * @brief setLoadSpec set the LoadSpec to the slave node
     * @param loadSpec ref to theinstance of the LoadSpec, the INode will copy the loadSpec instance
     */
    virtual void setLoadSpec(const DataSet::Control::LoadSpec& loadSpec) = 0;

    virtual void dispatchJob() = 0;

    virtual void init() = 0;
    virtual void loadData() = 0;
    virtual void start() = 0;
    virtual void stop(int taskId = -1) = 0;
    virtual bool destory() = 0;

};

}


#endif // INODE_HH
