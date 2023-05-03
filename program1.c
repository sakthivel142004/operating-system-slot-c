#include <stdio.h>
#define NUM_PROCESSES 4
#define NUM_RESOURCES 3
int main() {
    int claim[NUM_PROCESSES][NUM_RESOURCES] = {{3, 2, 2},
                                                {6, 1, 3},
                                                {3, 1, 4},
                                                {4, 2, 2}};
    int allocation[NUM_PROCESSES][NUM_RESOURCES] = {{1, 0, 0},
                                                     {6, 1, 2},
                                                     {2, 1, 1},
                                                     {0, 0, 2}};
    int resource[NUM_RESOURCES] = {9, 3, 6};
    int available[NUM_RESOURCES] = {0};
    for (int j = 0; j < NUM_RESOURCES; j++) {
        int allocated_resources = 0;
        for (int i = 0; i < NUM_PROCESSES; i++) {
            allocated_resources += allocation[i][j];
        }
        available[j] = resource[j] - allocated_resources;
    }
    int finish[NUM_PROCESSES] = {0};
    int finished_processes = 0;
    while (finished_processes < NUM_PROCESSES) {
        int found = 0;
        for (int i = 0; i < NUM_PROCESSES; i++) {
            if (finish[i] == 0) {
                int can_finish = 1;
                for (int j = 0; j < NUM_RESOURCES; j++) {
                    if (claim[i][j] - allocation[i][j] > available[j]) {
                        can_finish = 0;
                        break;
                    }
                }
                if (can_finish) {
                    found = 1;
                    finish[i] = 1;
                    for (int j = 0; j < NUM_RESOURCES; j++) {
                        available[j] += allocation[i][j];
                    }
                    finished_processes++;
                }
            }
        }
        if (!found) {
            printf("System is in unsafe state.\n");
            return 0;
        }
    }
    printf("System is in safe state.\n");
    return 0;
}
