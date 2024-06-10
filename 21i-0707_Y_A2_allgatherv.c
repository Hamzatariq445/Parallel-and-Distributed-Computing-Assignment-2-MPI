//Hamza Tariq
//i210707
//Assignment 2


#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void my_allgatherv(void *sendbuf, int sendcount, MPI_Datatype sendtype,
                   void *recvbuf, int *recvcounts, int *displs, MPI_Datatype recvtype,
                   MPI_Comm comm) {
    int rank, size;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    for (int i = 0; i < size; i++) {
    
            MPI_Send(sendbuf, sendcount, sendtype, i, 0, comm);
        
    }

    for (int i = 0; i < size; i++) {
            MPI_Recv((char *)recvbuf + displs[i] * sizeof(recvtype), recvcounts[i], recvtype, i, 0, comm, MPI_STATUS_IGNORE);
        
    }
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int send_data = rank;

    int *recv_data = (int *)malloc(size * sizeof(int));

    int sendcount = 1;
    int recvcounts[size];
    int displs[size];
    for (int i = 0; i < size; i++) {
        recvcounts[i] = 1;
        displs[i] = i;
    }

    my_allgatherv(&send_data, sendcount, MPI_INT, recv_data, recvcounts, displs, MPI_INT, MPI_COMM_WORLD);

    printf("Rank %d received: ", rank);
    for (int i = 0; i < size; i++) {
        printf("%d ", recv_data[i]);
    }
    printf("\n");

    free(recv_data);
    MPI_Finalize();
    return 0;
}
