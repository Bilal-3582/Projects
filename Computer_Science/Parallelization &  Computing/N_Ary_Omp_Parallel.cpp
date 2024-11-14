#include <iostream>
#include <vector>
#include <omp.h> // OpenMP library

using namespace std;

// Function to perform N-Ary Search with OpenMP
int nArySearchOMP(const vector<int>& arr, int target, int N) {
    int left = 0, right = arr.size() - 1;

    while (left <= right) {
        // Calculate the partition size
        int partitionSize = (right - left + 1) / N;
        if (partitionSize == 0) partitionSize = 1;

        vector<int> dividers(N + 1);
        
        // Calculate all division points in parallel
        #pragma omp parallel for
        for (int i = 0; i <= N; i++) {
            dividers[i] = left + i * partitionSize;
            if (dividers[i] > right) dividers[i] = right + 1; // Ensure it doesn't go out of bounds
        }

        // Check each divider in parallel
        int foundIndex = -1;
        #pragma omp parallel for shared(foundIndex)
        for (int i = 0; i < N; i++) {
            if (foundIndex != -1) continue; // Early exit if found

            int mid = dividers[i];
            if (mid > right) continue;

            if (arr[mid] == target) {
                #pragma omp critical
                foundIndex = mid;
            } else if (arr[mid] > target) {
                #pragma omp critical
                right = mid - 1;
            } else if (i == N - 1) {
                #pragma omp critical
                left = dividers[i] + 1;
            }
        }

        if (foundIndex != -1)
            return foundIndex;
    }
    return -1; // Target not found
}

int main() {
    int n, N, target;
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the sorted array elements:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Enter the target to search: ";
    cin >> target;

    cout << "Enter the value of N (for N-Ary search): ";
    cin >> N;

    int result = nArySearchOMP(arr, target, N);

    if (result != -1)
        cout << "Element found at index " << result << endl;
    else
        cout << "Element not found" << endl;

    return 0;
}
