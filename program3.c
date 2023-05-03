#include <stdio.h>
#define NUM_PROCESSES 4
struct Process {
    int id;
    int burst_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
};
void swap(struct Process* a, struct Process* b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}
void sort_by_burst_time(struct Process* processes, int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (processes[j].burst_time > processes[j+1].burst_time) {
                swap(&processes[j], &processes[j+1]);
            }
        }
    }
}
void compute_waiting_time(struct Process* processes, int n) {
    int total_waiting_time = 0;
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        processes[i].waiting_time = current_time - processes[i].arrival_time;
        if (processes[i].waiting_time < 0) {
            processes[i].waiting_time = 0;
        }
        total_waiting_time += processes[i].waiting_time;
        current_time += processes[i].burst_time;
    }
    double avg_waiting_time = (double) total_waiting_time / n;
    printf("Average waiting time: %.2lf\n", avg_waiting_time);
}
void compute_turnaround_time(struct Process* processes, int n) {
    int total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }
    double avg_turnaround_time = (double) total_turnaround_time / n;
    printf("Average turnaround time: %.2lf\n", avg_turnaround_time);
}
int main() {
    struct Process processes[NUM_PROCESSES] = {
        {1, 6, 0},
        {2, 8, 0},
        {3, 7, 0},
        {4, 3, 0}
    };
    sort_by_burst_time(processes, NUM_PROCESSES);
    compute_waiting_time(processes, NUM_PROCESSES);
    compute_turnaround_time(processes, NUM_PROCESSES);
    return 0;
}
