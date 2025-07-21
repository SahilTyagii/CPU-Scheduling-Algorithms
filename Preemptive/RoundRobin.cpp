#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Process {
public:
    int id;
    int arrivalTime;
    int burstTime;
    int turnAroundTime;
    int completionTime;
    int waitTime;
    int remainingTime;
    Process(int id, int arrivalTime, int burstTime): id(id), arrivalTime(arrivalTime), burstTime(burstTime), remainingTime(burstTime) {}
    void print() {
        cout << "\nP" << id << ": \n";
        cout << "Arrival Time: " << arrivalTime << endl;
        cout << "Burst Time: " << burstTime << endl;
        cout << "Completion Time: " << completionTime << endl;
        cout << "Turn Around Time: " << turnAroundTime << endl;
        cout << "Wait Time: " << waitTime << endl;
    }
};

int main() {
    int n, quantum;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter the time quantum: ";
    cin >> quantum;
    vector<Process*> processes(n);
    for (int i = 0; i < n; ++i) {
        int arrivalTime, burstTime;
        cout << i + 1 << "th process\n";
        cout << "Enter arrival Time: ";
        cin >> arrivalTime;
        cout << "Enter burst Time: ";
        cin >> burstTime;
        processes[i] = new Process(i + 1, arrivalTime, burstTime);
    }

    sort(processes.begin(), processes.end(), [&] (Process* a, Process* b) {
        return a->arrivalTime < b->arrivalTime;
    });

    queue<Process*> q;

    int time = 0, completed = 0, i = 0;
    while (completed < n) {
        while (i < n && processes[i]->arrivalTime <= time) {
            q.push(processes[i]);
            i++;
        }
        
        if (!q.empty()) {
            Process* p = q.front();
            q.pop();

            int execTime = min(p->remainingTime, quantum);
            p->remainingTime -= execTime;
            time += execTime;

            if (p->remainingTime == 0) {
                p->completionTime = time;
                
                p->turnAroundTime = p->completionTime - p->arrivalTime;
                p->waitTime = p->turnAroundTime - p->burstTime;

                completed++;
            } else {
                q.push(p);
            }
        } else {
            time = processes[i]->arrivalTime;
        }
    }

    for (Process* p: processes) {
        p->print();
        delete p;
    }

    return 0;
}