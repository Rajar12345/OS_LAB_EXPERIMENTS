#include <stdio.h>
#include <stdbool.h>
#define N 2 
int turn;
bool flag[N];
void init() 
{
    for (int i = 0; i < N; i++) 
    {
        flag[i] = false;
    }
    turn = 0;
}

void lock(int process) 
{
    int other = 1 - process;
    flag[process] = true; 
    turn = process;
    while (flag[other] && turn == process) 
    {
    }
}
void unlock(int process) 
{
    flag[process] = false;  
}
void critical_section(int process)
{
    printf("Process %d is in the critical section.\n", process);
}
void non_critical_section(int process) 
{
    printf("Process %d is in the non-critical section.\n", process);
}
void process(int process_id) 
{
    for (int i = 0; i < 5; i++) 
    {
        lock(process_id);
        critical_section(process_id);
        unlock(process_id);
        non_critical_section(process_id);
    }
}
int main() 
{
    init();
    process(0);
    process(1);
    return 0;
}

