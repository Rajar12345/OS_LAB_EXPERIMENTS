#include<stdio.h>

struct Process 
{
    int pid;
    int bt;
    int priority;
};

void findWaitingTime(struct Process proc[], int n, int wt[]) 
{
    wt[0] = 0;
  
    for (int i = 1; i < n ; i++ ) 
    {
        wt[i] = proc[i-1].bt + wt[i-1] ;
    }
}

void findTurnAroundTime( struct Process proc[], int n, int wt[], int tat[]) 
{
    for (int i = 0; i < n ; i++) 
    {
        tat[i] = proc[i].bt + wt[i];
    }
}

void findAvgTime(struct Process proc[], int n) 
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
  
    findWaitingTime(proc, n, wt);
  
    findTurnAroundTime(proc, n, wt, tat);
  
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
  
    for (int i=0; i<n; i++) 
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
  
        printf("%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].bt, wt[i], tat[i]);
    }
  
    printf("\nAverage waiting time: %f", (float)total_wt/n);
    printf("\nAverage turnaround time: %f", (float)total_tat/n);
}

int main() 
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
  
    struct Process proc[n];
  
    printf("Enter the burst time and priority for each process:\n");
    for (int i = 0; i < n; i++) 
    {
        printf("Process %d:\n", i+1);
        printf("Burst Time: ");
        scanf("%d", &proc[i].bt);
        printf("Priority: ");
        scanf("%d", &proc[i].priority);
        proc[i].pid = i+1;
    }

    for (int i = 0; i < n; i++) 
    {
        for (int j = i+1; j < n; j++) 
        {
            if (proc[i].priority > proc[j].priority) 
            {
                struct Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
  
    findAvgTime(proc, n);
  
    return 0;
}
