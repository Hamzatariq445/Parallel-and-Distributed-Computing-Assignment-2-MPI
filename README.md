# Parallel-and-Distributed-Computing-Assignment-2-MPI

1. Implement the following problem scenario using MPI functions. You can use point
to point and any collective functions?
"Travelling Salesman Problem" (TSP). The TSP involves finding the shortest possible route that
visits a set of cities and returns to the starting city, without visiting any city more than once. It is
a classic optimization problem with numerous real-world applications, such as logistics and
transportation. Parallelizing the TSP can provide significant performance improvements,
especially for large problem instances. Represent the TSP as a graph, where cities are nodes, and
edges represent the distances between cities. Choose an appropriate data structure for efficient
graph representation, such as adjacency matrices or adjacency lists.
Parallel algorithm design: Design a parallel algorithm for solving the TSP using MPI. Divide the
problem into sub-problems that can be solved independently. One approach is to partition the
cities among multiple computing nodes, where each node solves the TSP for its assigned subset
of cities.
Parallel search: Implement a parallel search strategy to explore different routes
simultaneously. This can be done using techniques like parallel depth-first search or parallel
branch-and-bound. Each computing node explores a portion of the solution space independently,
eliminating the need for inter-node communication during the search.
Inter-node communication: Depending on the parallel algorithm design, you may need to
incorporate inter-node communication for exchanging information or sharing intermediate
results. This can involve techniques like message passing or shared memory, depending on the
parallel programming framework you choose.
Performance evaluation: Evaluate the performance of the parallelized TSP solver in terms of
runtime, speedup, and scalability. Compare the results with a sequential TSP solver on the same
problem instances.

2. Implement the following functions using point to point (ptop) functions ONLY.
• MPI_Allgather
• Similar to MPI_Gather, but the result is available to all processes
• MPI_Allgatherv
• Similar to MPI_Gatherv, but the result is available to all processes

• MPI_Alltoall
• Similar to MPI_Allgather, each process performs a scater followed by gather
process
• MPI_Alltoallv
• Similar to MPI_Alltoall, but messages to different processes can have different
length
