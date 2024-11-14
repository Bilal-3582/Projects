#include <mpi.h>
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

#define INF INT_MAX

void floydWarshallMPI(vector<vector<int>>& dist, int n, int rank, int size) {
    int rowsPerProcess = n / size;
    int extraRows = n % size;
    int startRow = rank * rowsPerProcess + min(rank, extraRows);
    int endRow = startRow + rowsPerProcess - 1 + (rank < extraRows ? 1 : 0);

    // Each process works on its assigned rows
    for (int k = 0; k < n; k++) {
        // Broadcast the k-th row to all processes
        MPI_Bcast(dist[k].data(), n, MPI_INT, k / rowsPerProcess, MPI_COMM_WORLD);

        // Perform updates for the assigned rows
        for (int i = startRow; i <= endRow; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Gather results from all processes
    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            int recvStartRow = i * rowsPerProcess + min(i, extraRows);
            int recvEndRow = recvStartRow + rowsPerProcess - 1 + (i < extraRows ? 1 : 0);
            for (int r = recvStartRow; r <= recvEndRow; r++) {
                MPI_Recv(dist[r].data(), n, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }
    } else {
        for (int i = startRow; i <= endRow; i++) {
            MPI_Send(dist[i].data(), n, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n;
    vector<vector<int>> dist;

    if (rank == 0) {
        cout << "Enter the number of vertices: ";
        cin >> n;

        dist.resize(n, vector<int>(n));
        cout << "Enter the adjacency matrix (use " << INF << " for no edge):" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> dist[i][j];
            }
        }
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank != 0) {
        dist.resize(n, vector<int>(n, INF));
    }

    for (int i = 0; i < n; i++) {
        MPI_Bcast(dist[i].data(), n, MPI_INT, 0, MPI_COMM_WORLD);
    }

    floydWarshallMPI(dist, n, rank, size);

    if (rank == 0) {
        cout << "Shortest Path Distance Matrix:" << endl;
        for (const auto& row : dist) {
            for (int val : row) {
                if (val == INF)
                    cout << "INF\t";
                else
                    cout << val << "\t";
            }
            cout << endl;
        }
    }

    MPI_Finalize();
    return 0;
}
