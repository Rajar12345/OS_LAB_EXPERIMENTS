#include <stdio.h>
#include <stdlib.h>

struct Process 
{
    int id;
    int priority;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
};

int findHighestPriority(struct Process processes[], int n) 
{
    int highest_priority = -1;
    int highest_priority_idx = -1;

    for (int i = 0; i < n; i++) 
    {
        if (processes[i].remaining_time > 0 && processes[i].priority > highest_priority) 
        {
            highest_priority = processes[i].priority;
            highest_priority_idx = i;
        }
    }

    return highest_priority_idx;
}

int main() 
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process *processes = (struct Process *)malloc(n * sizeof(struct Process));

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter priority for Process P%d: ", i + 1);
        scanf("%d", &processes[i].priority);
        printf("Enter burst time for Process P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
    }

    int time = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    while (1) {
        int highest_priority_idx = findHighestPriority(processes, n);

        if (highest_priority_idx == -1)
            break;

        processes[highest_priority_idx].remaining_time--;

        time++;

        if (processes[highest_priority_idx].remaining_time == 0) {
            processes[highest_priority_idx].turnaround_time = time;
            total_waiting_time += processes[highest_priority_idx].waiting_time;
            total_turnaround_time += processes[highest_priority_idx].turnaround_time;
        }

        for (int i = 0; i < n; i++) {
            if (i != highest_priority_idx && processes[i].remaining_time > 0) {
                processes[i].waiting_time++;
            }
        }
    }

    printf("\nProcess Table:\n");
    printf("-----------------------------------------------------------\n");
    printf("| Process | Priority | Burst Time | Waiting Time | Turnaround Time |\n");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("|   P%d    |    %2d    |     %2d      |      %2d      |        %2d        |\n",
               processes[i].id, processes[i].priority, processes[i].burst_time,
               processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("-----------------------------------------------------------\n");

    float average_waiting_time = (float)total_waiting_time / n;
    float average_turnaround_time = (float)total_turnaround_time / n;

    printf("\nAverage Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);

    free(processes);

    return 0;
}
