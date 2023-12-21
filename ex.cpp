
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to check if the system is in a safe state
bool isSafe(vector<vector<int>>& need, vector<vector<int>>& alloc, vector<int>& avail, int n, int m) {
    vector<bool> finished(n, false);
    vector<int> safeSeq(n);
    vector<int> work = avail;

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int p = 0; p < n; p++) {
            if (!finished[p]) {
                int j;
                for (j = 0; j < m; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == m) {
                    for (int k = 0; k < m; k++)
                        work[k] += alloc[p][k];

                    safeSeq[count++] = p;
                    finished[p] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            cout << "System is not in safe state\n";
            return false;
        }
    }

    cout << "System is in a safe state.\nSafe sequence is: ";
    for (int i = 0; i < n; i++)
        cout << "P" << safeSeq[i] << " ";
    cout << "\n";
    return true;
}

int main() {
    srand(time(NULL)); // Seed for random number generation

    int n, m;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resources: ";
    cin >> m;

    vector<vector<int>> alloc(n, vector<int>(m));
    vector<vector<int>> max(n, vector<int>(m));
    vector<vector<int>> need(n, vector<int>(m));
    vector<int> avail(m);

    // Generate allocation and maximum matrices
    cout << "Generating allocation and maximum matrices...\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            alloc[i][j] = rand() % 5; // Random allocation
            max[i][j] = alloc[i][j] + rand() % 5; // Random max, ensuring it's >= allocation
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Generate available resources
    cout << "Generating available resources...\n";
    for (int i = 0; i < m; i++) {
        avail[i] = rand() % 10; // Random available resources
    }

    // Display generated data
    cout << "Allocation Matrix:\n";
    for (auto &row : alloc) {
        for (int val : row) cout << val << " ";
        cout << "\n";
    }

    cout << "Maximum Matrix:\n";
    for (auto &row : max) {
        for (int val : row) cout << val << " ";
        cout << "\n";
    }

    cout << "Available Resources:\n";
    for (int val : avail) cout << val << " ";
    cout << "\n";

    // Check if the system is in a safe state
    isSafe(need, alloc, avail, n, m);

    return 0;
}
