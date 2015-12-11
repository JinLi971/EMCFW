#include "NodeUtils.hh"
#include <mpi.h>
#include <cassert>

namespace Node {
namespace Utils {

void GroupHelpers::constructGroup(DataSet::Control::LoadSpec &loadSpec, int taskId)
{
    MPI_Group worldGroup;

    MPI_Comm_group(MPI_COMM_WORLD, &worldGroup);

    std::map<int, DataSet::Control::LoadSpec::GroupStruct>& groupMap =
            loadSpec.getGroup();

    std::map<int, DataSet::Control::LoadSpec::GroupStruct>::iterator iter =
            groupMap.begin();

    while(iter != groupMap.end())
    {
        DataSet::Control::LoadSpec::GroupStruct& group = iter->second;

        int retVal = MPI_Group_incl(worldGroup,
                                    group.cluster.size(),
                                    group.getClusterList(),
                                    &(group.group));
        assert(retVal == MPI_SUCCESS);

        retVal = MPI_Comm_split(MPI_COMM_WORLD, group.color, taskId, &(group.comm));
        assert(retVal == MPI_SUCCESS);

        MPI_Group_rank(group.group, &(group.taskId));
    }
}



}
}
