#include <iostream>
using namespace std;

struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int remaining;  // Remaining time
    int completion; // Completion time
};

void findCompletionTimes(Process proc[], int n, int quantum) {
    int time = 0, completed = 0;
    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining > 0) {
                if (proc[i].remaining > quantum) {
                    // Process gets a full quantum
                    time += quantum;
                    proc[i].remaining -= quantum;
                } else {
                    // Process finishes execution in less than a quantum
                    time += proc[i].remaining;
                    proc[i].completion = time;
                    proc[i].remaining = 0;
                    completed++;
                }
            }
        }
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
    int n, quantum;
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

    cout << "Enter the time quantum: ";
    cin >> quantum;

    findCompletionTimes(proc, n, quantum);
    calculateTurnaroundTimes(proc, n, tat);
    calculateWaitingTimes(proc, n, tat, wt);
    display(proc, n, tat, wt);

    return 0;
}
