#include <stdio.h>
#include <stdlib.h>
#define MAX_PARTITIONS 10
int partitions[MAX_PARTITIONS];
int num_partitions;
void initialize_partitions() {
    num_partitions = 6;
    partitions[0] = 300;
    partitions[1] = 600;
    partitions[2] = 350;
    partitions[3] = 200;
    partitions[4] = 750;
    partitions[5] = 125;
}
void print_partitions() {
    printf("\nMemory partitions: ");
    for (int i = 0; i < num_partitions; i++) {
        printf("%d KB ", partitions[i]);
    }
    printf("\n");
}
int first_fit(int process_size) {
    for (int i = 0; i < num_partitions; i++) {
        if (partitions[i] >= process_size) {
            partitions[i] -= process_size;
            return i;
        }
    }
    return -1;
}
int main() {
    initialize_partitions();
    print_partitions();
    int process_sizes[] = {115, 500, 358, 200, 375};
    int num_processes = sizeof(process_sizes) / sizeof(int);
    for (int i = 0; i < num_processes; i++) {
        int partition_index = first_fit(process_sizes[i]);
        if (partition_index >= 0) {
            printf("Process of size %d KB is placed in partition %d.\n", process_sizes[i], partition_index);
        } else {
            printf("Process of size %d KB cannot be placed.\n", process_sizes[i]);
        }
    }
    print_partitions();
    return 0;
}

