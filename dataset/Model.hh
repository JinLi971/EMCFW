#ifndef MODEL_HH
#define MODEL_HH

#include <spimage.h>

namespace DataSet
{

class Model
{
public:
    Model(unsigned int x, unsigned int y, unsigned int z, const real *data);
    Model(const sp_3matrix* matrix);

    virtual ~Model();

    int getX() { return mData.x; }
    int getY() { return mData.y; }
    int getZ() { return mData.z; }
    real* getData() { return mData.data; }

private:
    sp_3matrix mData;
};

}

#endif // MODEL_HH
