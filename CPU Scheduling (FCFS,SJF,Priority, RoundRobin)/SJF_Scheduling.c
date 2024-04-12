#include <stdio.h>

void sjfScheduling(int n, int bt[]) 
{
    int wt[n], tat[n], temp;
    float total_wt = 0, total_tat = 0;

    // Sorting the burst times in ascending order using Bubble Sort
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (bt[j] > bt[j + 1]) 
            {
                // Swapping burst times
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;
            }
        }
    }

    // Calculating waiting time for each process
    wt[0] = 0;
    for (int i = 1; i < n; i++) 
    {
        wt[i] = bt[i - 1] + wt[i - 1];
        total_wt += wt[i];
    }

    // Calculating turnaround time for each process
    for (int i = 0; i < n; i++) 
    {
        tat[i] = bt[i] + wt[i];
        total_tat += tat[i];
    }

    // Displaying process details
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) 
    {
        printf("   %d\t   %d\t\t   %d\t\t   %d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    // Calculating average waiting time and average turnaround time
    float avg_wt = total_wt / n;
    float avg_tat = total_tat / n;
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
}

int main() 
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst_time[n];
    printf("Enter burst times for each process:\n");
    for (int i = 0; i < n; i++) 
    {
        printf("Process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }
    sjfScheduling(n, burst_time);

    return 0;
}
