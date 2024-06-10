#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <mpi.h>

#define NUM_CITIES 4 

int calculate_cost(int path[], int adj_matrix[NUM_CITIES][NUM_CITIES]) {
  int cost = 0;
  for (int i = 0; i < NUM_CITIES - 1; i++) {
    cost += adj_matrix[path[i]][path[i + 1]];
  }
  
  cost += adj_matrix[path[NUM_CITIES - 1]][path[0]];
  return cost;
}


void next_permutation(int perm[], int n) {
  int i = n - 1;
  while (i > 0 && perm[i - 1] >= perm[i]) {
    i--;
  }
  if (i <= 0) {
    return;
  }

  int j = n - 1;
  while (perm[j] <= perm[i - 1]) {
    j--;
  }

  int temp = perm[i - 1];
  perm[i - 1] = perm[j];
  perm[j] = temp;

  j = n - 1;
  while (i < j) {
    temp = perm[i];
    perm[i] = perm[j];
    perm[j] = temp;
    i++;
    j--;
  }
}

int main(int argc, char *argv[]) {
  int rank, size;
  
  
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (size < 2) {
    fprintf(stderr, "At least 2 processes required\n");
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  double start_time = MPI_Wtime();
  int adj_matrix[NUM_CITIES][NUM_CITIES] = {
        {0, 1, 1, 1},
        {1, 0, 10, 5},
        {1, 10, 0, 20},
        {1, 5, 20, 0}
};

  int total_perms = 1;
  for (int i = 1; i <= NUM_CITIES; i++) {
    total_perms *= i;
  }
  

  int perms_per_process = total_perms / size;
  int start_idx = rank * perms_per_process;
  int end_idx = (rank + 1) * perms_per_process;

  int least_cost = INT_MAX;
  int least_path[NUM_CITIES];
  int perm[NUM_CITIES];

  for (int i = 0; i < NUM_CITIES; i++) {
    perm[i] = i; 
  }

  for (int i = start_idx; i < end_idx; i++) {
    int temp_cost = calculate_cost(perm, adj_matrix);
    if (temp_cost < least_cost) {
      least_cost = temp_cost;
      for (int j = 0; j < NUM_CITIES; j++) {
        least_path[j] = perm[j];
      }
    }
    next_permutation(perm, NUM_CITIES);
  }

  int global_least_cost;
  int global_least_path[NUM_CITIES];

  MPI_Reduce(&least_cost, &global_least_cost, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    printf("Least cost: %d\n", global_least_cost);
  }

  MPI_Gather(least_path, NUM_CITIES, MPI_INT, global_least_path, NUM_CITIES, MPI_INT, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    printf("Least cost path: ");
    for (int i = 0; i < NUM_CITIES; i++) {
      printf("%d ", global_least_path[i]);
    }
    printf("\n");
  }
  
  double end_time = MPI_Wtime();
  double elapsed_time = end_time - start_time;

  if (rank == 0) {
    printf("Elapsed time: %f seconds\n", elapsed_time);
  }

  MPI_Finalize();
  
   

  return 0;
}
