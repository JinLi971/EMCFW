#ifndef MASK_HH
#define MASK_HH

#include <spimage.h>

namespace DataSet
{

class Mask
{
public:
    Mask(const sp_imatrix *matrix);
    Mask(unsigned int rows, unsigned int cols, const int *data);

    virtual ~Mask();

    unsigned int getRows() { return mData.rows; }
    unsigned int getCols() { return mData.cols; }
    const int *getMask() { return mData.data; }

private:
    sp_imatrix mData;
};

}

#endif // MASK_HH
