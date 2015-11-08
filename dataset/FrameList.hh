#ifndef FRAMELIST_HH
#define FRAMELIST_HH

#include <vector>
#include <cstdio>

namespace DataSet
{

class Frame;

class FrameList
{
public:
    FrameList();
    virtual ~FrameList();

    const std::vector<Frame *> getFrameList();
    void addFrame(Frame *frame);
    void removeFrame(unsigned int index);
    void removeFrame(const Frame* frame);

    size_t getLength();    
    void clear();

private:
    std::vector<Frame *> mList;
};

}

#endif // FRAMELIST_HH
