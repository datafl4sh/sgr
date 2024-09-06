/* ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <datafl4sh@toxicnet.eu> wrote this file. As long as you retain this notice
 * you can do whatever you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me a beer in return.
 * Matteo Cicuttin - https://github.com/datafl4sh/sgr
 * ----------------------------------------------------------------------------
 */

#include "sgr/sgr.hpp"

int main(int argc, char **argv)
{
    using namespace sgr;

#ifdef SGR_ENABLE_MPI
    MPI_Init(&argc, &argv);
#endif

    int my_rank = 0;
#ifdef SGR_ENABLE_MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
#endif

    std::cout << "[not filtered] hello from rank " << my_rank << std::endl;
    std::cout << rank(0) << "[filtered] hello from rank " << my_rank << std::endl;

#ifdef SGR_ENABLE_MPI
    MPI_Finalize();
#endif

    return 0;
}