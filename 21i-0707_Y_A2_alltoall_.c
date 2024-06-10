//hamza Tariq
//i210707
//Assignmnet 2
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int send_count = 1;
    int recv_count = 1;
    int send_data[size];
    int recv_data[size];

    for (int i = 0; i < size; i++) {
        send_data[i] = rank * size + i;
        recv_data[i] = 0;
    }

    for (int i = 0; i < size; i++) {
        MPI_Request request;
        MPI_Isend(&send_data[i], send_count, MPI_INT, i, 0, MPI_COMM_WORLD, &request);
        MPI_Recv(&recv_data[i], recv_count, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Wait(&request, MPI_STATUS_IGNORE);
    }

    printf("Rank %d received:\n", rank);
    for (int i = 0; i < size; i++) {
        printf("%d ", recv_data[i]);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}
