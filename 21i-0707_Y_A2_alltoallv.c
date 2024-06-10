//hamza Tariq
//i210707
//Assignmnet 2
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *sendbuf = NULL;
    int sendcounts[size];
    int senddispls[size];
    int total_send = size * size;

    sendbuf = (int *)malloc(total_send * sizeof(int));
    for (int i = 0; i < total_send; i++) {
        sendbuf[i] = rank * size + i % size;
    }

    for (int i = 0; i < size; i++) {
        sendcounts[i] = size;
        senddispls[i] = i * size;
    }

    int *recvbuf = NULL;
    int recvcounts[size];
    int recvdispls[size];
    int total_recv = size * size;

    recvbuf = (int *)malloc(total_recv * sizeof(int));

    for (int i = 0; i < size; i++) {
        recvcounts[i] = size;
        recvdispls[i] = i * size;
    }

    MPI_Alltoallv(sendbuf, sendcounts, senddispls, MPI_INT,
                  recvbuf, recvcounts, recvdispls, MPI_INT, MPI_COMM_WORLD);

    printf("Rank %d: ", rank);
    for (int i = 0; i < total_recv; i++) {
        printf("%d ", recvbuf[i]);
    }
    printf("\n");

    free(sendbuf);
    free(recvbuf);

    MPI_Finalize();
    return 0;
}
