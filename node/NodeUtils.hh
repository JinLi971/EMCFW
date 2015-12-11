#ifndef NODEUTILS_HH
#define NODEUTILS_HH

#include "dataset/control/LoadSpec.hh"


namespace Node {
namespace Utils {

class GroupHelpers
{
public:
    static void constructGroup(DataSet::Control::LoadSpec& loadSpec, int taskId);
};

}
}


#endif // NODEUTILS_HH
