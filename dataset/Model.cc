#include "Model.hh"

namespace DataSet
{

Model::Model(unsigned int x, unsigned int y, unsigned int z, const real *data)
{
    mData.x = x;
    mData.y = y;
    mData.z = z;

    unsigned long size = x * y * z;
    mData.data = new real[size];
    memcpy(mData.data, data, size);
}

Model::Model(const sp_3matrix *matrix)
{
    mData.x = matrix->x;
    mData.y = matrix->y;
    mData.z = matrix->z;

    unsigned long size = matrix->x * matrix->y * matrix->z;
    mData.data = new real[size];
    memcpy(mData.data, matrix->data, size);
}

Model::~Model()
{
    delete mData.data;
}

}
