#include <mpi.h>
#include <iostream>
#include <vector>

using namespace std;

// Function to perform N-Ary Search with MPI
int nArySearchMPI(const vector<int>& arr, int target, int N, int rank, int size) {
    int left = 0, right = arr.size() - 1;
    int localResult = -1;

    while (left <= right) {
        int partitionSize = (right - left + 1) / N;
        if (partitionSize == 0) partitionSize = 1;

        int start = rank * partitionSize;
        int end = (rank == size - 1) ? (right - left) : ((rank + 1) * partitionSize - 1);

        for (int i = left + start; i <= left + end && i <= right; i++) {
            if (arr[i] == target) {
                localResult = i;
                break;
            }
        }

        MPI_Allreduce(MPI_IN_PLACE, &localResult, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);

        if (localResult != -1)
            return localResult;

        if (rank == size - 1)
            left = left + end + 1;
        else
            right = left + start - 1;
    }
    return -1;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n, N, target;
    vector<int> arr;

    if (rank == 0) {
        cout << "Enter the number of elements in the array: ";
        cin >> n;
        arr.resize(n);
        cout << "Enter sorted array elements: ";
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        cout << "Enter the target element: ";
        cin >> target;
        cout << "Enter the value of N (for N-Ary search): ";
        cin >> N;
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&target, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank != 0) {
        arr.resize(n);
    }

    MPI_Bcast(arr.data(), n, MPI_INT, 0, MPI_COMM_WORLD);

    int result = nArySearchMPI(arr, target, N, rank, size);

    if (rank == 0) {
        if (result != -1)
            cout << "Element found at index " << result << endl;
        else
            cout << "Element not found" << endl;
    }

    MPI_Finalize();
    return 0;
}
