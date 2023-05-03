#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;
void calculate_waiting_time(Process *processes, int n) {
    int remaining_times[n];
    for (int i = 0; i < n; i++) {
        remaining_times[i] = processes[i].burst_time;
    }
    int completed_processes = 0, time = 0, shortest_time_index = -1, prev_shortest_time_index = -1;
    while (completed_processes < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && remaining_times[i] > 0) {
                if (shortest_time_index == -1 || remaining_times[i] < remaining_times[shortest_time_index]) {
                    shortest_time_index = i;
                }
            }
        }
        if (shortest_time_index != prev_shortest_time_index) {
            processes[shortest_time_index].waiting_time += time - processes[shortest_time_index].turnaround_time;
            prev_shortest_time_index = shortest_time_index;
        }
        remaining_times[shortest_time_index]--;
        if (remaining_times[shortest_time_index] == 0) {
            completed_processes++;
            int completion_time = time + 1;
            processes[shortest_time_index].turnaround_time = completion_time - processes[shortest_time_index].arrival_time;
            shortest_time_index = -1;
        }
        time++;
    }
}
void calculate_turnaround_time(Process *processes, int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
    }
}
void calculate_average_times(Process *processes, int n, double *avg_waiting_time, double *avg_turnaround_time) {
    calculate_waiting_time(processes, n);
    calculate_turnaround_time(processes, n);
    double total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }
    *avg_waiting_time = total_waiting_time / n;
    *avg_turnaround_time = total_turnaround_time / n;
}
int main() {
    int n = 4;
    Process processes[] = {{1, 0, 5, 5, 0, 0}, {2, 1, 3, 3, 0, 0}, {3, 2, 3, 3, 0, 0}, {4, 4, 1, 1, 0, 0}};
    double avg_waiting_time, avg_turnaround_time;
    calculate_average_times(processes, n, &avg_waiting_time, &avg_turnaround_time);
    printf("Average waiting time = %.2f ms\n", avg_waiting_time);
    printf("Average turnaround time = %.2f ms\n", avg_turnaround_time);
    return 0;
}

