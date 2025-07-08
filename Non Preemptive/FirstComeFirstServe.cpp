#include <iostream>
#include <vector>
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
    Process(int id, int arrivalTime, int burstTime): id(id), arrivalTime(arrivalTime), burstTime(burstTime) {}
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
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
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

    int time = 0;
    for (Process* p: processes) {
        if (p->arrivalTime < time) {
            p->completionTime = time + p->burstTime;
            time = p->completionTime;
        } else {
            p->completionTime = p->arrivalTime + p->burstTime;
            time = p->completionTime;
        }
        p->turnAroundTime = p->completionTime - p->arrivalTime;
        p->waitTime = p->turnAroundTime - p->burstTime;
    }

    for (Process* p: processes) {
        p->print();
    }

    for (Process* p: processes) {
        delete p;
    }

    return 0;
}