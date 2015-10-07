#include "FrameList.hh"
#include "Frame.hh"
#include <algorithm>

namespace DataSet {

FrameList::FrameList()
{
}

FrameList::~FrameList()
{
    mList.clear();
}

const std::vector<Frame *> FrameList::getFrameList()
{
    return mList;
}

void FrameList::addFrame(Frame *frame)
{
    mList.push_back(frame);
}

void FrameList::removeFrame(unsigned int index)
{
    mList.erase(mList.begin() + index);
}

void FrameList::removeFrame(const Frame *frame)
{
    std::vector<Frame *>::iterator frameResult =  std::find(mList.begin(), mList.end(), frame);
    if (frameResult != mList.end()) {
        mList.erase(frameResult);
    }
}

void FrameList::clear()
{
    mList.clear();
}

size_t FrameList::getLength()
{
    return mList.size();
}

}

