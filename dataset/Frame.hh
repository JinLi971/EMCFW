#ifndef FRAME_HH
#define FRAME_HH

#include <spimage.h>

namespace DataSet
{

class Frame
{
public:
    Frame(unsigned int x, unsigned int y, const real* data);
    Frame(const sp_matrix *matrix);

    virtual ~Frame();

    unsigned int getRows() { return mData.rows; }
    unsigned int getCols() { return mData.cols; }
    const real *getFrame() { return mData.data; }

    virtual bool operator ==(Frame& obj) const;

private:
    sp_matrix mData;
};

}

#endif // FRAME_HH
