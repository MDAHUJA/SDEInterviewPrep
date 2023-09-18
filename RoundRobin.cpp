#include <iostream>
#include <queue>

using namespace std;

// Structure to represent a process
struct Process {
    int id;
    int burstTime;
};

int main() {
    // Number of processes
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    // Time quantum (fixed time slice for each process)
    int timeQuantum;
    cout << "Enter the time quantum: ";
    cin >> timeQuantum;

    // Create a queue to hold the processes
    queue<Process> processQueue;

    // Input process details
    for (int i = 1; i <= n; ++i) {
        Process process;
        process.id = i;
        cout << "Enter burst time for Process " << i << ": ";
        cin >> process.burstTime;
        processQueue.push(process);
    }

    // Simulate RR scheduling
    cout << "Process Execution Order:" << endl;
    while (!processQueue.empty()) {
        Process currentProcess = processQueue.front();
        processQueue.pop();

        // Execute the process for the time quantum or its remaining burst time, whichever is smaller
        int executionTime = min(timeQuantum, currentProcess.burstTime);
        cout << "Executing Process " << currentProcess.id << " for " << executionTime << " units" << endl;

        // Update the burst time for the process
        currentProcess.burstTime -= executionTime;

        // If the process has remaining burst time, push it back into the queue
        if (currentProcess.burstTime > 0) {
            processQueue.push(currentProcess);
        }
    }

    cout << "All processes have completed execution." << endl;

    return 0;
}
