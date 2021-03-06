#include <gtest/gtest.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    ::testing::InitGoogleTest(&argc, argv);
    int rtv = RUN_ALL_TESTS();

    MPI_Finalize();

    return rtv;
}
