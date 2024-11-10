#include <iostream>
#include <vector>

using namespace std;

class BankersAlgorithm {
private:
    int processes;          // Number of processes
    int resources;          // Number of resource types
    vector<vector<int>> maxResources;   // Maximum resources required by each process
    vector<vector<int>> allocated;      // Resources currently allocated to each process
    vector<int> available;              // Available instances of resources
    vector<vector<int>> need;           // Resources needed by each process to finish

public:
    // Constructor to initialize the system with the number of processes, resources, etc.
    BankersAlgorithm(int p, int r, vector<vector<int>> max, vector<vector<int>> alloc, vector<int> avail) {
        processes = p;
        resources = r;
        maxResources = max;
        allocated = alloc;
        available = avail;

        // Calculate the need matrix
        need.resize(processes, vector<int>(resources));
        for (int i = 0; i < processes; ++i) {
            for (int j = 0; j < resources; ++j) {
                need[i][j] = maxResources[i][j] - allocated[i][j];
            }
        }
    }

    // Function to check if the system is in a safe state
    bool isSafe() {
        vector<int> work = available;    // Available resources
        vector<bool> finish(processes, false); // Flag for finished processes
        int count = 0;

        while (count < processes) {
            bool found = false;

            for (int i = 0; i < processes; ++i) {
                if (!finish[i]) {
                    // Check if the process can finish with the current available resources
                    bool canFinish = true;
                    for (int j = 0; j < resources; ++j) {
                        if (need[i][j] > work[j]) {
                            canFinish = false;
                            break;
                        }
                    }

                    if (canFinish) {
                        // If it can finish, simulate it and release the allocated resources
                        for (int j = 0; j < resources; ++j) {
                            work[j] += allocated[i][j];
                        }
                        finish[i] = true;
                        ++count;
                        found = true;
                    }
                }
            }

            if (!found) {
                // If no process can proceed, then the system is in an unsafe state
                return false;
            }
        }

        // If all processes can finish, the system is in a safe state
        return true;
    }

    // Function to request resources
    bool requestResources(int processId, vector<int>& request) {
        // Step 1: Check if request is less than or equal to need
        for (int i = 0; i < resources; ++i) {
            if (request[i] > need[processId][i]) {
                cout << "Process " << processId << " has exceeded its maximum claim." << endl;
                return false;
            }
        }

        // Step 2: Check if request is less than or equal to available resources
        for (int i = 0; i < resources; ++i) {
            if (request[i] > available[i]) {
                cout << "Resources not available for Process " << processId << "." << endl;
                return false;
            }
        }

        // Step 3: Temporarily allocate requested resources and check safety
        vector<int> originalAvailable = available;
        vector<vector<int>> originalAllocation = allocated;
        vector<vector<int>> originalNeed = need;

        // Allocate requested resources
        for (int i = 0; i < resources; ++i) {
            available[i] -= request[i];
            allocated[processId][i] += request[i];
            need[processId][i] -= request[i];
        }

        // Check if the system is in a safe state after the allocation
        if (isSafe()) {
            cout << "Request granted for Process " << processId << "." << endl;
            return true;
        } else {
            // Rollback if the request leads to an unsafe state
            available = originalAvailable;
            allocated = originalAllocation;
            need = originalNeed;
            cout << "Request denied for Process " << processId << " as it would lead to an unsafe state." << endl;
            return false;
        }
    }

    // Function to release resources after process completion
    void releaseResources(int processId, vector<int>& release) {
        for (int i = 0; i < resources; ++i) {
            allocated[processId][i] -= release[i];
            available[i] += release[i];
            need[processId][i] = maxResources[processId][i] - allocated[processId][i];
        }
        cout << "Resources released by Process " << processId << "." << endl;
    }
};

int main() {
    // Example input

    // Number of processes and resources
    int p = 5;  // 5 processes
    int r = 3;  // 3 resource types

    // Maximum demand of resources for each process
    vector<vector<int>> maxResources = {
        {7, 5, 3},  // Process 0
        {3, 2, 2},  // Process 1
        {9, 0, 2},  // Process 2
        {2, 2, 2},  // Process 3
        {4, 3, 3}   // Process 4
    };

    // Resources currently allocated to each process
    vector<vector<int>> allocated = {
        {0, 1, 0},  // Process 0
        {2, 0, 0},  // Process 1
        {3, 0, 2},  // Process 2
        {2, 1, 1},  // Process 3
        {0, 0, 2}   // Process 4
    };

    // Available resources
    vector<int> available = {3, 3, 2};

    // Initialize the Banker's Algorithm system
    BankersAlgorithm bankers(p, r, maxResources, allocated, available);

    // Request resources for Process 1
    vector<int> request1 = {1, 0, 2};
    bankers.requestResources(1, request1);

    // Request resources for Process 4
    vector<int> request2 = {3, 3, 0};
    bankers.requestResources(4, request2);

    // Release resources by Process 0
    vector<int> release = {1, 0, 0};
    bankers.releaseResources(0, release);

    // Request resources for Process 2
    vector<int> request3 = {4, 0, 1};
    bankers.requestResources(2, request3);

    return 0;
}
