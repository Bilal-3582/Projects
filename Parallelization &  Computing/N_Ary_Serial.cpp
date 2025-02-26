#include <iostream>
#include <vector>
using namespace std;

// Function to perform N-Ary Search on a sorted array
int nArySearch(const vector<int>& arr, int target, int N) {
    int left = 0, right = arr.size() - 1;

    while (left <= right) {
        // Calculate the partition size
        int partitionSize = (right - left + 1) / N;
        if (partitionSize == 0) partitionSize = 1;

        // Check all divisions
        vector<int> dividers;
        for (int i = 1; i < N; i++) {
            dividers.push_back(left + i * partitionSize);
        }

        // Add right boundary as the last division point
        dividers.push_back(right + 1);

        // Check each divider
        for (int i = 0; i < dividers.size() - 1; i++) {
            int mid = dividers[i];

            if (arr[mid] == target)
                return mid; // Target found

            if (arr[mid] > target) {
                right = mid - 1; // Adjust the search to the left part
                break;
            }
            else if (i == dividers.size() - 2) {
                left = dividers[i] + 1; // Move search to the right part
            }
        }
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

    int result = nArySearch(arr, target, N);

    if (result != -1)
        cout << "Element found at index " << result << endl;
    else
        cout << "Element not found" << endl;

    return 0;
}
