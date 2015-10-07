#include "Frame.hh"

namespace DataSet
{

Frame::Frame(const sp_matrix *matrix)
{
    assert(matrix->cols > 0);
    assert(matrix->rows > 0);

    mData.cols = matrix->cols;
    mData.rows = matrix->rows;

    mData.data = new real[mData.cols * mData.rows];
    memcpy(mData.data, matrix->data, matrix->cols * matrix->rows);
}

Frame::Frame(unsigned int rows, unsigned int cols, const real *data)
{
    assert(rows > 0);
    assert(cols > 0);

    mData.cols = cols;
    mData.rows = rows;

    mData.data = new real[mData.cols * mData.rows];
    memcpy(mData.data, data, cols * rows);
}

Frame::~Frame()
{
    delete mData.data;
}

bool Frame::operator==(Frame &obj) const
{
    // Compare if the data ptr is point to identical dataset
    // Here is ptr comparison
    if (mData.data == obj.getFrame()) {
        return true;
    }

    return false;
}

}
