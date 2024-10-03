#include <stdio.h>

#define MAX_PROCESS 10

struct process {
    char name[10];
    int arrival_time;
    int burst_time;
    int remaining_time;
};

int main() {
    FILE *fp;
    char filename[20];
    int quantum_time;
    struct process processes[MAX_PROCESS];
    int n, i, time = 0, total_turnaround_time = 0;

    printf("Enter file name: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: could not open file %s\n Either you are running the code in online complier or file could not be access, Kindly contact the Deepak for more information.", filename);
        return 1;
    }

    printf("Enter quantum time: ");
    scanf("%d", &quantum_time);

    // Read in the processes from the file
    n = 0;
    while (fscanf(fp, "%s %d %d", processes[n].name, &processes[n].arrival_time, &processes[n].burst_time) == 3) {
        processes[n].remaining_time = processes[n].burst_time;
        n++;
    }

    fclose(fp);

    // Execute the processes using Round Robin scheduling
    while (1) {
        int all_done = 1;

        for (i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                all_done = 0;

                // Execute the process for one quantum time
                if (processes[i].remaining_time > quantum_time) {
                    time += quantum_time;
                    processes[i].remaining_time -= quantum_time;
                } else {
                    time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;

                    // Compute the turnaround time for this process
                    int turnaround_time = time - processes[i].arrival_time;
                    total_turnaround_time += turnaround_time;
                    printf("Turnaround time for %s is %d\n", processes[i].name, turnaround_time);
                }
            }
        }

        // Check if all processes are done
        if (all_done) {
            break;
        }
    }

    // Compute the average turnaround time for all processes
    float avg_turnaround_time = (float)total_turnaround_time / n;
    printf("Average turnaround time for all processes is %.2f\n", avg_turnaround_time);

    return 0;
}
