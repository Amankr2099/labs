#include <iostream>
using namespace std;
#define INT_MAX 2147483647

struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int remaining;  // Remaining time
    int completion; // Completion time
};

void findCompletionTimes(Process proc[], int n) {
    int time = 0, completed = 0, min_index = -1;
    int shortest_remaining_time = INT_MAX;
    bool check = false;

    while (completed != n) {
        // Find the process with the shortest remaining time
        for (int i = 0; i < n; i++) {
            if (proc[i].arrival <= time && proc[i].remaining > 0 && proc[i].remaining < shortest_remaining_time) {
                shortest_remaining_time = proc[i].remaining;
                min_index = i;
                check = true;
            }
        }

        if (!check) {
            time++;
            continue;
        }

        // Decrement the remaining time of the shortest process
        proc[min_index].remaining--;
        shortest_remaining_time = proc[min_index].remaining;

        // If process gets completely executed
        if (proc[min_index].remaining == 0) {
            completed++;
            check = false;
            proc[min_index].completion = time + 1;
            shortest_remaining_time = INT_MAX;
        }

        time++;
    }
}

void calculateTurnaroundTimes(Process proc[], int n, int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = proc[i].completion - proc[i].arrival;
    }
}

void calculateWaitingTimes(Process proc[], int n, int tat[], int wt[]) {
    for (int i = 0; i < n; i++) {
        wt[i] = tat[i] - proc[i].burst;
    }
}

void display(Process proc[], int n, int tat[], int wt[]) {
    cout << "PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (int i = 0; i < n; i++) {
        cout << proc[i].pid << "\t" << proc[i].arrival << "\t" << proc[i].burst
             << "\t" << proc[i].completion << "\t\t" << tat[i] << "\t\t" << wt[i] << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process proc[n];
    int tat[n], wt[n];

    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> proc[i].arrival >> proc[i].burst;
        proc[i].pid = i + 1;
        proc[i].remaining = proc[i].burst;
    }

    findCompletionTimes(proc, n);
    calculateTurnaroundTimes(proc, n, tat);
    calculateWaitingTimes(proc, n, tat, wt);
    display(proc, n, tat, wt);

    return 0;
}
