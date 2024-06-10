//hamza Tariq
//i210707
//Assignmnet 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int sendbuf = rank;
    int recvbuf[size];

    for (int i = 0; i < size; i++) {
        MPI_Send(&sendbuf, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    }

	for (int i = 0; i < size; i++) {
    	    MPI_Recv(&recvbuf[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	    printf("Rank %d received %d from %d\n", rank, recvbuf[i], i);
	}

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Finalize();
    return 0;
}
