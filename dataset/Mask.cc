#include "Mask.hh"

namespace DataSet
{

Mask::Mask(const sp_imatrix *matrix)
{
    assert(matrix->cols > 0);
    assert(matrix->rows > 0);

    mData.cols = matrix->cols;
    mData.rows = matrix->rows;

    mData.data = new int[mData.cols * mData.rows];
    memcpy(mData.data, matrix->data, matrix->cols * matrix->rows);
}

Mask::Mask(unsigned int rows, unsigned int cols, const int *data)
{
    assert(rows > 0);
    assert(cols > 0);

    mData.cols = cols;
    mData.rows = rows;

    mData.data = new int[mData.cols * mData.rows];
    memcpy(mData.data, data, cols * rows);
}

Mask::~Mask()
{
    delete mData.data;
}

}
