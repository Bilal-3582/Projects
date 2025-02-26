#include <iostream>
#include <vector>
#include <algorithm>
#include <climits> // For INT_MAX

using namespace std;

#define INF INT_MAX

// Function to implement the Floyd-Warshall algorithm
void floydWarshall(vector<vector<int>>& dist, vector<vector<int>>& pred, int n) {
    // Initialize predecessor matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && dist[i][j] != INF)
                pred[i][j] = i;
            else
                pred[i][j] = -1; // No predecessor if no edge exists
        }
    }

    // Floyd-Warshall Algorithm
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // If vertex k is on the shortest path from i to j, then update the value of dist[i][j]
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    pred[i][j] = pred[k][j];
                }
            }
        }
    }
}

// Utility function to print a matrix
void printMatrix(const vector<vector<int>>& matrix, const string& name) {
    cout << name << " Matrix:" << endl;
    for (const auto& row : matrix) {
        for (int val : row) {
            if (val == INF)
                cout << "INF\t";
            else
                cout << val << "\t";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of vertices: ";
    cin >> n;

    // Initialize distance matrix
    vector<vector<int>> dist(n, vector<int>(n));
    vector<vector<int>> pred(n, vector<int>(n));

    cout << "Enter the adjacency matrix (use " << INF << " for no edge):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dist[i][j];
        }
    }

    floydWarshall(dist, pred, n);

    printMatrix(dist, "Distance");
    printMatrix(pred, "Predecessor");

    return 0;
}
